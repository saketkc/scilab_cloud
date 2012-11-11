import subprocess
import simplejson as json
from django.http import HttpResponseRedirect
from django.http import HttpResponse
from django.shortcuts import render_to_response
import re
import os
from reportlab.pdfgen import canvas
import datetime
from reportlab.lib.units import inch
from django.views.decorators.csrf import csrf_exempt
def scilab_instances(request,scilab_code):
    process = subprocess.Popen(['scilab-cli -nb -nwni -e '+scilab_code],shell=True,stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    output = process.communicate()[0]
    output = output.strip()
    print output
    return HttpResponse(json.dumps({"input":scilab_code,"output":output,"graph":""}))

    """if first_time:
        scilab_instance = pexpect.spawn('scilab-cli -nb -nwni')
        scilab_instance.expect('-->')
        request.session['scilab'] = scilab_instance
    else:
        scilab_instance = request.session['scilab']
	output = ""
	for i in range(0,len(scilab_code)):
		print scilab_code[i]
		scilab_instance.sendline(str(scilab_code[i]))
		scilab_instance.expect('-->')
		output = output + str(scilab_instance.before.replace("\r\n\x1b[?1h\x1b=","").replace("\r\n\x1b[?1l\x1b>","").replace(str(scilab_code[i]),""))
	output.replace(all_code,"")
	return output"""


def default_view(request):
	try:
		user_id = request.session['user_id']
	except:
		return HttpResponseRedirect("/login")

	return render_to_response('../public/default.html',{'input':'//Type Code Here','uid':user_id,'username':request.session['username']})
@csrf_exempt
def scilab_new_evaluate(request):
    if request.method =="GET":

        return render_to_response('../public/default.html',{'input':'//Type Code Here','uid':request.session['user_id'],'username':request.session['username']})
    all_code = request.POST.get('scilab_code')
    filter_for_system = re.compile("unix_g|unix_x|unix_w|unix_s|host|newfun|execstr")
    if  (filter_for_system.findall(all_code)):
        return HttpResponse(json.dumps({'input':'System commnads are not supported','uid':request.session['user_id'],'username':request.session['username'],'output':'System commands are disabled','graph':'','graphs':''  }),'application/json')
    print request.POST
    graphics_mode = request.POST.get('graphicsmode')
    print "GARPHICSMODE",graphics_mode
    if not graphics_mode:
        print "No GRAPHS REQUIRED"
        cwd = "/home/cfduser/SANDBOX/scilab_cloud" + "/graphs/" + str(request.session['user_id'])
        if not os.path.exists(cwd):
            os.makedirs(cwd)
        filename=datetime.datetime.now().strftime("%Y-%m-%d%H-%M-%S")
        all_code  = all_code +"\n quit();"
        filetowrite = open(cwd+"/"+filename+".sce","w")
        filetowrite.write(all_code)
        filetowrite.close()
        filetoread = cwd+"/"+filename+".sce"
        process = subprocess.Popen('scilab-cli -nb -nwni -f '+filetoread ,shell=True,stdin=subprocess.PIPE,stdout=subprocess.PIPE)
        print all_code
        #try:
	soutput = process.communicate()[0]
        #soutsoutput.replace("\000b","")
        soutput = soutput.strip()
        #    signal.alarm(0)
        #except:
        #    soutput ="Taking too long . Maybe there was an error"

        print soutput

        return HttpResponse(json.dumps({"input":all_code,"output":soutput,"graph":""}),'application/json')
        #scilab_instances(request,all_code)

    original_code = all_code

    #print all_code

    cwd = "/home/cfduser/SANDBOX/scilab_cloud" + "/graphs/" + str(request.session['user_id'])
    filename=datetime.datetime.now().strftime("%Y-%m-%d%H-%M-%S")
    cwdsf = cwd +"/"+ filename +"-code.sce"
    if not os.path.exists(cwd):
        os.makedirs(cwd)
    f = open(cwdsf,"w")
    user_id = str(request.session['user_id'])
    graph = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S").replace(" ","")
    all_code = "driver(\"PNG\");\n" + "\n xinit(\""+cwd+"/"+graph+".png\");\n" + all_code+ "\nxend();\n" + "\nquit();"
    f.write(all_code)
    f.close()
    p=subprocess.Popen("/opt/scilab/bin/scilab-adv-cli -nb -f "+ cwdsf , shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
#    try:
    out, err = p.communicate()
 #   signal.alarm(0)
  #  except:
   #     out="Taking too long. Maybe ther was an errror"
    print out

    #print 'proc1\'s pid =',p.pid
    #time.sleep(2)
    #p.terminate()

    #return render_to_response('../public/default.html',{'input':original_code,'uid':request.session['user_id'],'username':request.session['username'],'graphs':graphs,'output':out,'graph':'graph.png'})
    return HttpResponse(json.dumps({"input":original_code,"output":out,"graph":graph,"user_id":user_id}),'application/json')

"""def scilab_evaluate(request):

	try:
		user_id = request.session['user_id']
	except:
		return HttpResponseRedirect("/cloud")
        all_code = request.POST.get('scilab_code')
        if not all_code:
		return HttpResponseRedirect("/scilab_view")
	all_code = all_code.replace(" ","")
	graphics_mode = request.POST.get('graphicsmode')
	all_code = all_code.replace("//Type Code Here","")
	filter_for_system = re.compile("unix_g|unix_x|unix_w|unix_s")
	if not (filter_for_system.findall(all_code)):
			split_code = all_code.split()
			plot_filter = re.compile("plot2d\(.*\)")
			function_filter = re.compile("deff\(.*\)")
			variable =[]
			expression = []
			the_data_set = {}
			output = ""
			the_variable = ""
			graphs = []
			links = []
			for i in range(0,len(split_code)):
				plot_data = plot_filter.findall(split_code[i])
				function_data = function_filter.findall(split_code[i])
				if function_data:
					#a=sciscipy.eval(split_code[i])
					#re_fnname = re.compile("\[.*\]=.*\(.*,.\)")
					#fn_data = re_fnname.findall(split_code[i])
					return_variables = scilab_instances(split_code,all_code)
					#eval("function_name = fn_data[0].split('=')[1]")
					return render_to_response('default.html',{'input':all_code,             'output':return_variables , 'username':request.session['username']})
					#return_variables = eval('sci.function_name')
					#print return_variables
					#return HttpResponse(return_variables)
				split_more = split_code[i].split("=")
				if (len(split_more)>1):
					expression.append(split_more[1])
					evaluated_code = sciscipy.eval(split_code[i])
					the_variable = split_code[i].split("=")[0]
					the_variable_value =  sciscipy.read(the_variable)
					the_data_set[the_variable] = the_variable_value
					output = output +str(the_variable) + " =\n " + "    " + str(the_variable_value) + "\n"
				if plot_data:
					coordinates = plot_data[0].split("(")[1].split(")")[0].split(",")
					x=coordinates[0]
					y=coordinates[1]
					plt.plot(the_data_set[x],the_data_set[y])
		           	        graphs.append('simple_plot' + str(i))
					cwd = str(os.getcwd()) + "/graphs/" + str(request.session['user_id'])
					cwdsf = cwd + str(graphs[-1])
					if not os.path.exists(cwd):
					    os.makedirs(cwd)
					plt.savefig(cwdsf)
			for graph in graphs:
				p = canvas.Canvas(cwd+str(graph)+".pdf",pagesize=letter)
				links.append(str(request.META['SERVER_NAME'])+":"+str(request.META['SERVER_PORT']) + str(graph))
                        	p.drawImage(cwd+str(graph)+".png", 1*inch,1*inch, width=5*inch,height=5*inch,mask=None)
                       		p.showPage()
	                   	p.save()
			return render_to_response('default.html',{'input':all_code,  		'output':output , "graphs":graphs,'username':request.session['username'],"links":links})
        else:
		return render_to_response('default.html',{'input':all_code,'output':"error"})


"""
def download(request,graphname):
	response = HttpResponse(mimetype='application/pdf')
	response['Content-Disposition'] = 'attachment; filename='+str(graphname)+'.pdf'
	p = canvas.Canvas(response)
	cwd = "/home/cfduser/SANDBOX/scilab_cloud" + "/graphs/" + str(request.session['user_id'])+"/"
	p.drawImage(cwd+str(graphname)+".png", 1*inch,1*inch, width=5*inch,height=5*inch,mask=None)
        p.showPage()
 	p.save()
        return response
