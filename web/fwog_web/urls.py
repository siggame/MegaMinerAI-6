#Fwog_web urls.
from django.conf.urls.defaults import *

urlpatterns = patterns('',
    # Example:
    (r'^$', 'web.fwog_web.views.index'),
    (r'^stats$','web.fwog_web.views.stats'),
    (r'^stat/poll/$', 'web.fwog_web.views.poll'),
    (r'^results/(?P<result>.*)$', 'web.fwog_web.views.results'),
    (r'^docs$', 'web.fwog_web.views.docs'),
    (r'^poll_result/(?P<result>.*)$', 'web.fwog_web.views.poll_result'),
)
