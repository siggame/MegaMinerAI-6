from django.http                import HttpResponse, HttpResponseRedirect
from django.template            import Context, loader
from django.core.urlresolvers   import reverse
from django.contrib.auth.models import User
from django.contrib.auth        import logout
from web.registration.forms     import RegistrationCode, SignUp
from web.registration.models    import RegistrationCode as RegistrationModel

def index(request):
    warning = ''
    try:
        reg_code = request.REQUEST['reg_code']
    except KeyError:
        return HttpResponseRedirect(reverse('web.fwog_web.views.index'))
    if request.method == 'POST':
        print "yes post"
        form = SignUp(request.POST)
        if form.is_valid():
            if form.cleaned_data['password'] != form.cleaned_data['password_again']:
                warning = "Password Mismatch"
            elif not RegistrationModel.objects.filter(code=reg_code, usedBy="").exists():
                warning = "Bad Registration Code. Bother a dev."
            else:
                try:
                    user = User.objects.create_user(str(form.cleaned_data['username']).lower(), 
                                                    '',
                                                    form.cleaned_data['password'])
                    user.save()
                    r = RegistrationModel.objects.filter(code=reg_code)[0]
                    r.usedBy = form.cleaned_data['username']
                    r.save()
                    t = loader.get_template('registration/registered.html')
                    c = Context({"username": form.cleaned_data['username']})
                    return HttpResponse(t.render(c))
                except Exception, e:
                    print e
                    warning = "User already exists. Try another name"

    else:
        print "get blank form"
        form = SignUp()

    print "last last return"
    t = loader.get_template('registration/register.html')
    c = Context({"reg_code": reg_code,
                 "form":form,
                 "warning":warning})
    return HttpResponse(t.render(c))

def logout_user(request):
    logout(request)
    return HttpResponseRedirect(reverse('web.fwog_web.views.index'))

def change_password(request):
    pass
