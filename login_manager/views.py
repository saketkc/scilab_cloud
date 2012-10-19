from django.http import HttpResponse,HttpResponseRedirect

from django.shortcuts import render_to_response
import _mysql
#import hashlib
from django.views.decorators.csrf import csrf_exempt

def logout(request):

	del request.session['user_id']
	del request.session['username']
	return HttpResponseRedirect("/")

@csrf_exempt
def login(request):
	if request.method == "POST":
		username = request.POST['username']
		password = request.POST['password']
		db = _mysql.connect("localhost","root","fedora13","scilab")
		query ="SELECT pass,uid FROM users where name="+"'"+str(username)+"'"
		db.query(query)
		result = db.store_result()
		result = result.fetch_row()
		password_from_db = result[0][0]
		user_id = result[0][1]
		#md5 = hashlib.md5(password).hexdigest()
		md5 = password
		if str(md5) == str(password_from_db):
			request.session['user_id'] = user_id
			request.session['username'] = username
			request.session['first_time']= True
			return HttpResponseRedirect("/scilab_view")
		return HttpResponse(str(md5) + " "+ str(password_from_db))
	else :
		return render_to_response("login.html")

