from django.db import models
from django.contrib.auth.models import User
from datetime import datetime

# Create your models here.

class Bug(models.Model):
    CATEGORIES=((u'none', u''),
                (u'vis', u'Visualizer'),
                (u'web', u'Web Server'),
                (u'server', u'Game Server/Logic'),
                (u'client',u'Game Client'))
    STATUSES=((u'new', u'New'),
              (u'as', u'Assigned'),
              (u'ip', u'Fixing...'),
              (u'done', u'Fixed'))
    submitter = models.ForeignKey(User, related_name="submitting_user")
    fixer = models.CharField(max_length=50)
    time_opened = models.DateTimeField()
    time_updated = models.DateTimeField()
    subject = models.CharField(max_length=80)
    description = models.TextField()
    category = models.CharField(max_length=50, choices = CATEGORIES)
    status = models.CharField(max_length=10, choices=STATUSES)
    

    def save(self):
        if self.time_opened == None:
            self.time_opened = datetime.now()
        self.time_updated = datetime.now()
        super(Bug, self).save()

    def dictify(self):
        if self.status == 'new':
            status_color = 'red'
        elif self.status == 'done':
            status_color = 'green'
        elif self.status == 'as':
            status_color = 'orange'
        else:
            status_color = 'yellow'

        d = {'id' : self.id,
             'submitter' : self.submitter.username,
             'fixer' : self.fixer,
             'time_opened' : self.time_opened.isoformat(' '),
             'time_updated' : self.time_updated.isoformat(' '),
             'subject' : self.subject,
             'category' : self.get_category_display(),
             'description' : self.description,
             'status':self.get_status_display(),
             'status_color': status_color}
        return d

    def is_active(self):
        return self.status != 'done'

    def is_fixer(self, username):
        return self.fixer == username
