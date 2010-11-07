from django.http                    import HttpResponse, HttpResponseRedirect
from django.template                import Context, loader
from web.bugtracker.models          import Bug
from django.core.urlresolvers       import reverse
from django.contrib.auth.decorators import login_required    
from web.bugtracker.models          import Bug
from web.bugtracker.forms           import BugForm, BugUpdateForm
from datetime                       import datetime
import json

@login_required
def index(request):
    t = loader.get_template('fwog_web/bugs.html')
    c = Context({'user': request.user.username,
                 'bugs': True})
    return HttpResponse(t.render(c))

@login_required
def bug_details(request, bug_id):
    form=None
    bug = Bug.objects.filter(id=bug_id)[0]
    if request.user.is_staff:
        if request.method=='POST':
            form = BugUpdateForm(request.POST)
            if form.is_valid():
                bug.status = form.cleaned_data['status']
                bug.category = form.cleaned_data['category']
                s = form.cleaned_data['description']
                s = '\n\n'+datetime.now().isoformat(' ')+'==> '+s
                bug.description += s
                bug.fixer=request.user.username
                bug.save()
                return HttpResponseRedirect(
                    reverse('web.bugtracker.views.index'))
        else:
            form = BugUpdateForm(auto_id='id_for_%s')
    t = loader.get_template('fwog_web/bug_details.html')
    c = Context({'user': request.user.username,
                 'bugs': True,
                 'bug': bug.dictify(),
                 'form':form,
                 'default_select_category':bug.category,
                 'default_select_status':bug.status})
    return HttpResponse(t.render(c))

@login_required
def new_bug(request):
    if request.method == 'POST':
        form = BugForm(request.POST)
        if form.is_valid():
            b = Bug(submitter=request.user,
                    fixer="No one...",
                    subject=form.cleaned_data['subject'],
                    description=form.cleaned_data['description'],
                    category=form.cleaned_data['category'],
                    status="new")
            b.save()
            return HttpResponseRedirect(
                reverse('web.bugtracker.views.index'))
    else:
        form = BugForm()

    t = loader.get_template('fwog_web/new_bug.html')
    c = Context({'user': request.user.username,
                 'bugs': True,
                 'form': form})
    return HttpResponse(t.render(c))    

@login_required
def poll(request):
    bugs = Bug.objects.all()
    user_bugs = Bug.objects.filter(submitter=request.user)
    fixer_bugs = Bug.objects.filter(fixer=request.user.username)

    bug_dicts = map(lambda x: x.dictify(), 
                    filter(lambda x: x.is_active(), bugs))

    user_bug_dicts = map(lambda x: x.dictify(), user_bugs)
    fixer_bug_dicts = map(lambda x: x.dictify(), fixer_bugs)

    d = {'bugs':bug_dicts, 'user_bugs':user_bug_dicts+fixer_bug_dicts}

    return HttpResponse(json.dumps(d))

