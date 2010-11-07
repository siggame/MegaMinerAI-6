from django.db import models
import json
from django.contrib.auth.models import User
from datetime import datetime

class Info(models.Model):
    message = models.CharField(max_length=500)
    user = models.CharField(max_length = 100)
    active = models.BooleanField()
    
    @classmethod
    def get_message(self):
        max_id = Info.objects.aggregate(models.Max('id'))['id__max']
        if max_id != None:
            current_message = Info.objects.filter(id=max_id)[0]
            if current_message.active:
                return current_message.message
        return ''

    @classmethod
    def new_message(self, message, user):
        max_id = Info.objects.aggregate(models.Max('id'))['id__max']
        if max_id != None:
            current_message = Info.objects.filter(id=max_id)[0]
            current_message.active = False
            current_message.save()
        else:
            max_id = -1
        i = Info(max_id+1, message, user, True)
        i.save()
    
    @classmethod
    def remove_message(self):
        for m in Info.objects.filter(active=True):
            m.active = False
            m.save()
        

class Game(models.Model):
    id = models.IntegerField(primary_key=True)
    player_1 = models.ForeignKey(User, related_name="p_1")
    player_2 = models.ForeignKey(User, related_name="p_2")
    player_1_version = models.IntegerField(null=False)
    player_2_version = models.IntegerField(null=False)
    player_1_score = models.IntegerField(null=False)
    player_2_score = models.IntegerField(null=False)
    log_name = models.CharField(max_length=150, unique=True)
    time = models.DateTimeField(default="CURRENT_TIMESTAMP")
    
    def __unicode__(self):
        return self.jsonify()

    def jsonify(self):
        d = {'id':self.id,
             'player_1':self.player_1.username,
             'player_1_version':self.player_1_version,
             'player_2':self.player_2.username,
             'player_1_version':self.player_2_version,
             'player_1_score':self.player_1_score,
             'player_2_score':self.player_2_score,
             'log_name':self.log_name,
             'time':self.time.isoformat(' ')}
        return unicode(json.dumps(d))

    def dictify(self):
        d = {'id':self.id,
             'player_1':self.player_1.username,
             'player_1_version':self.player_1_version,
             'player_2':self.player_2.username,
             'player_2_version':self.player_2_version,
             'player_1_score':self.player_1_score,
             'player_2_score':self.player_2_score,
             'log_name':self.log_name,             
             'time':self.time.isoformat(' ')}
        return d
    
    def dict_for_user(self, username):
        if self.player_1.username == username:
            user_score = self.player_1_score
            version = self.player_1_version
            opponent = self.player_2.username
            opponent_score = self.player_2_score
        elif self.player_2.username == username:
            user_score = self.player_2_score
            version = self.player_2_version
            opponent = self.player_1.username
            opponent_score = self.player_1_score
        else:
            opponent = "Could not determine opponent!"
            version = -1
            user_score = 0
            opponent_score = 0

        d = {'id':self.id,
             'opponent': opponent,
             'user_score': user_score,
             'opponent_score': opponent_score,
             'version':version,
             'log_name':self.log_name,
             'time':self.time.isoformat(' ')}
        return d
    
