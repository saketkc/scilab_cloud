from django.conf.urls.defaults import *
import os.path
from scilab_cloud import settings
from scilab_cloud.scilab_c.views import *
from scilab_cloud.login_manager.views import *
# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    (r'^$',login),
    (r'^login',login),
    (r'^scilab_view',default_view),
    (r'^logout',logout),
    (r'^scilab_evaluate',scilab_evaluate),
    (r'download/(?P<graphname>.*)/',download),
    (r'^public/(?P<path>.*)$', 'django.views.static.serve',{'document_root': settings.MEDIA_ROOT}),
    # url(r'^scilab_cloud/', include('scilab_cloud.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    # url(r'^admin/', include(admin.site.urls)),
)
