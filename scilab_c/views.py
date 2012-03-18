from django.core.mail import send_mail
from django.http import HttpResponseRedirect
from django.http import HttpResponse
from django.shortcuts import render_to_response
import commands
import re
import sciscipy
import os
import pexpect
import numpy
import pylab
from scilab import Scilab as sci
import reportlab
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter, A4
from reportlab.lib.units import inch
def scilab_instances(scilab_code,all_code):
	scilab_instance = pexpect.spawn('scilab-cli -nb -nwni')
	scilab_instance.expect('-->')
	output = ""
	for i in range(0,len(scilab_code)):
		print scilab_code[i]
		scilab_instance.sendline(str(scilab_code[i]))
		scilab_instance.expect('-->')
		output = output + str(scilab_instance.before.replace("\r\n\x1b[?1h\x1b=","").replace("\r\n\x1b[?1l\x1b>","").replace(str(scilab_code[i]),""))
	output.replace(all_code,"")
	return output	
		
def default_view(request):
	try:
		user_id = request.session['user_id']
	except:
		return HttpResponseRedirect("/login")

	return render_to_response('../public/default.html',{'input':'//Type Code Here','uid':request.session['user_id'],'username':request.session['username']})

def scilab_evaluate(request):
	
	try:
		user_id = request.session['user_id']
	except:
		return HttpResponseRedirect("/login")
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
					pylab.plot(the_data_set[x],the_data_set[y])
		           	        graphs.append('simple_plot' + str(i))
					cwd = str(os.getcwd()) + "/graphs/" + str(request.session['user_id'])
					cwdsf = cwd + str(graphs[-1])
					if not os.path.exists(cwd):
					    os.makedirs(cwd)
					pylab.savefig(cwdsf)
			for graph in graphs:
				p = canvas.Canvas(cwd+str(graph)+".pdf",pagesize=letter)
				links.append(str(request.META['SERVER_NAME'])+":"+str(request.META['SERVER_PORT']) + str(graph))
                        	p.drawImage(cwd+str(graph)+".png", 1*inch,1*inch, width=5*inch,height=5*inch,mask=None)
                       		p.showPage()
	                   	p.save()
			return render_to_response('default.html',{'input':all_code,  		'output':output , "graphs":graphs,'username':request.session['username'],"links":links})
        else:
		return render_to_response('default.html',{'input':all_code,'output':"error"})



def download(request,graphname):
	response = HttpResponse(mimetype='application/pdf')
	response['Content-Disposition'] = 'attachment; filename='+str(graphname)+'.pdf'
	p = canvas.Canvas(response)
	cwd = str(os.getcwd()) + "/graphs/" + str(request.session['user_id'])
	p.drawImage(cwd+str(graphname)+".png", 1*inch,1*inch, width=5*inch,height=5*inch,mask=None)
        p.showPage()
 	p.save()
        return response
