from web.fwog_web.models            import Game, Info
from web.fwog_web.forms             import InfoMessage
from django.http                    import HttpResponse, HttpResponseRedirect
from django.template                import Context, loader
from django.core.urlresolvers       import reverse
from django.contrib.auth.decorators import login_required    
import json

@login_required
def index(request):
    if request.user.is_staff and request.method == 'POST':
        form = InfoMessage(request.POST)
        if form.is_valid():
            if form.cleaned_data['remove']:
                Info.remove_message()
            else:
                Info.new_message(form.cleaned_data['message'], request.user.username)
    else:
        form = InfoMessage()
    info = Info.get_message()
    results = get_results(request)
    win_count = len(results['wins'])
    loss_count = len(results['losses'])
    if request.user.is_staff:
        image = 'whoomp.jpg'
    elif loss_count > win_count:
        image = 'watermelon.jpg'
    else:
        image = 'banana.jpg'
    t = loader.get_template('fwog_web/index.html')
    c = Context({'user': request.user.username,
                 'home': True,
                 'image':image,
                 'win_count':win_count,
                 'loss_count':loss_count,
                 'total':win_count+loss_count,
                 'info': info,
                 'is_staff':request.user.is_staff,
                 'form':form})
    return HttpResponse(t.render(c))

@login_required
def stats(request):
    d = get_results(request)
    t = loader.get_template('fwog_web/stats.html')
    c = Context({'user': request.user.username,
                 'stats': True,
                 'win_count':len(d['wins']),
                 'loss_count':len(d['losses']),
                 'wins':d['wins_5'],
                 'losses':d['losses_5'],
                 'ties':d['ties_5'],
                 'max_id':d['max_id'],
                 'max_results':d['max_results']})
    return HttpResponse(t.render(c))

@login_required
def results(request, result):
    if result not in ('wins', 'ties', 'losses'):
        return HttpResponseRedirect(reverse('web.fwog_web.views.stats'))
    else:
        d = get_results(request)
        t = loader.get_template('fwog_web/result.html')
        c = Context({'user': request.user.username,
                     'stats': True,
                     'result_name':result,
                     'result': d[result]})
        return HttpResponse(t.render(c))

@login_required
def docs(request):
    t = loader.get_template('fwog_web/docs.html')
    c = Context({'user': request.user.username,
                 'docs': True})
    return HttpResponse(t.render(c))

@login_required
def poll(request):
    played_games_p1 = Game.objects.filter(player_1=request.user)
    played_games_p2 = Game.objects.filter(player_2=request.user)

    (wins, losses, ties)=(list(), list(), list())

    for g in played_games_p1:
        if g.player_1_score > g.player_2_score:
            wins.append( g )
        elif g.player_1_score < g.player_2_score:
            losses.append( g )
        else:
            ties.append( g )
    for g in played_games_p2:
        if g.player_2_score > g.player_1_score:
            wins.append( g )
        elif g.player_2_score < g.player_1_score:
            losses.append( g )
        else:
            ties.append( g )

    wins.sort(key=lambda x: x.id)
    losses.sort(key=lambda x: x.id)
    ties.sort(key=lambda x: x.id)

    wins.reverse()
    losses.reverse()
    ties.reverse()

    if request.GET['max_id']:
        max_id = int(request.GET['max_id'])
    
        wins = filter(lambda x: x.id > max_id, wins)
        ties = filter(lambda x: x.id > max_id, ties)
        losses = filter(lambda x: x.id > max_id, losses)
        
        wins = map(lambda x: x.dict_for_user(request.user.username), wins)
        losses = map(lambda x: x.dict_for_user(request.user.username), losses)
        ties = map(lambda x: x.dict_for_user(request.user.username), ties)
        
        return HttpResponse(json.dumps({'wins':wins,
                                        'losses':losses,
                                        'ties':ties}))
    else:
        return HttpResponse(json.dumps({'wins':[],
                                        'losses':[],
                                        'ties':[]}))
@login_required
def poll_result(request, result):
    if "win" in result:
        op = ">"
    elif "tie" in result:
        op = "=="
    elif "los" in result:
        op = "<"
    played_games_p1 = Game.objects.filter(player_1=request.user)
    played_games_p2 = Game.objects.filter(player_2=request.user)

    results = list()

    def p1_results(x):
        return eval(str(x.player_1_score)+op+str(x.player_2_score))
    def p2_results(x):
        return eval(str(x.player_2_score)+op+str(x.player_1_score))

    results = filter(p1_results, played_games_p1)
    results.extend( filter(p2_results, played_games_p2) )

    results.sort(key=lambda x: x.id)

    results = map(lambda x: x.dict_for_user(request.user.username), results)

    return HttpResponse(json.dumps(results))



def get_results(request):
    played_games_p1 = Game.objects.filter(player_1=request.user)
    played_games_p2 = Game.objects.filter(player_2=request.user)

    (wins, losses, ties)=(list(), list(), list())

    for g in played_games_p1:
        if g.player_1_score > g.player_2_score:
            wins.append( g )
        elif g.player_1_score < g.player_2_score:
            losses.append( g )
        else:
            ties.append( g )
    for g in played_games_p2:
        if g.player_2_score > g.player_1_score:
            wins.append( g )
        elif g.player_2_score < g.player_1_score:
            losses.append( g )
        else:
            ties.append( g )

    wins.sort(key=lambda x: x.id)
    losses.sort(key=lambda x: x.id)
    ties.sort(key=lambda x: x.id)
    
    def f(lst):
        if len(lst) <= 5:
            return 0
        else:
            return len(lst)-5

    wins_5 = wins[f(wins) :]
    losses_5 = losses[f(losses) :]
    ties_5 = ties[f(ties) :]

    wins_5.reverse()
    losses_5.reverse()
    ties_5 .reverse()

    wins_5 = map(lambda x: x.dict_for_user(request.user.username), wins_5)
    losses_5 = map(lambda x: x.dict_for_user(request.user.username), losses_5)
    ties_5 = map(lambda x: x.dict_for_user(request.user.username), ties_5)

    wins = map(lambda x: x.dict_for_user(request.user.username), wins)
    losses = map(lambda x: x.dict_for_user(request.user.username), losses)
    ties = map(lambda x: x.dict_for_user(request.user.username), ties)

    try:
        max_id = max(map(lambda x: x['id'], wins_5+losses_5+ties_5))
        max_results = filter(lambda x: x['id'] == max_id, wins_5+losses_5+ties_5)[0]
    except ValueError:
        max_id = ''
        max_results = None

    return {'wins':wins,
            'ties':ties,
            'losses':losses,
            'wins_5':wins_5,
            'ties_5':ties_5,
            'losses_5':losses_5,
            'max_results':max_results,
            'max_id':max_id}
