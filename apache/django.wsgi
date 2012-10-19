import os
import sys
sys.path.append("/root/sciscipy-0.3.0")
sys.path.append("/root/SANDBOX")
sys.path.append("/root/SANDBOX/scilab_cloud")

os.environ['DJANGO_SETTINGS_MODULE'] = 'scilab_cloud.settings'

import django.core.handlers.wsgi
application = django.core.handlers.wsgi.WSGIHandler()

