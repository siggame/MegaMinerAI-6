#Fwog_web urls.
from django.conf.urls.defaults import *

urlpatterns = patterns('',
    # Example:
    (r'^$', 'web.bugtracker.views.index'),
    (r'^poll$', 'web.bugtracker.views.poll'),
    (r'^new_bug$', 'web.bugtracker.views.new_bug'),
    (r'^(?P<bug_id>.*)$', 'web.bugtracker.views.bug_details'),
)
