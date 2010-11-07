#Registration Urls.
from django.conf.urls.defaults import *

urlpatterns = patterns('',
    # Example:
    (r'^change_password$', 'web.registration.views.change_password'),
    (r'^login/$','django.contrib.auth.views.login', 
         {'template_name':'registration/login.html'}),
    (r'^logout/$', 'web.registration.views.logout_user'),
    (r'^register/$', 'web.registration.views.index'),
    (r'', 'web.fwog_web.views.index'),
)
