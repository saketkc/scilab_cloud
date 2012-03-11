from django.core.mail import send_mail
from django.http import HttpResponseRedirect
from django.http import HttpResponse
from django.shortcuts import render_to_response
import commands
import re
import sciscipy
import os
import numpy
import pylab
from scilab import Scilab
import reportlab
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter, A4
from reportlab.lib.units import inch
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
			variable =[]
			expression = []
			the_data_set = {}
			output = ""
			the_variable = ""
			graphs = []
			for i in range(0,len(split_code)):
				plot_data = plot_filter.findall(split_code[i])
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
			
                        	p.drawImage(cwd+str(graph)+".png", 1*inch,1*inch, width=5*inch,height=5*inch,mask=None)
                       		p.showPage()
	                   	p.save()
			return render_to_response('default.html',{'input':all_code,  		'output':output , "graphs":graphs})
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
