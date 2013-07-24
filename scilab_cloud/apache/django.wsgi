import os
import sys
sys.path.append("/home/cfduser/SANDBOX")
sys.path.append("/home/cfduser/SANDBOX/scilab_cloud")

os.environ['DJANGO_SETTINGS_MODULE'] = 'scilab_cloud.settings'

import django.core.handlers.wsgi
application = django.core.handlers.wsgi.WSGIHandler()

