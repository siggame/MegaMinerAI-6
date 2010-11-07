from django.conf.urls.defaults import *
import os

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
    # Example:
    (r'^accounts/', include('web.registration.urls')),
    (r'^bugs/', include('web.bugtracker.urls')),
    (r'^static/(?P<path>.*)$', 'django.views.static.serve',{'document_root': os.getcwd()+'/static/'}),
    (r'', include('web.fwog_web.urls')),
)
