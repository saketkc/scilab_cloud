from django.core.mail import send_mail
from django.http import HttpResponseRedirect
from django.http import HttpResponse
from django.shortcuts import render_to_response
import commands
import re
import sciscipy
import numpy
import pylab
from scilab import Scilab
import reportlab
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter, A4
from reportlab.lib.units import inch
def default_view(request):
	return render_to_response('default.html',{'input':'//Type Code Here'})

def scilab_evaluate(request):
	
        all_code = request.POST.get('scilab_code')
        all_code = all_code.replace(" ","")
	graphics_mode = request.POST.get('graphicsmode')
	all_code = all_code.replace("//Type Code Here","")
	filter_for_system = re.compile("unix_g|unix_x|unix_w|unix_s")
	if not (filter_for_system.findall(all_code)):
 		#if not graphics_mode:
			#response = HttpResponse(mimetype='application/pdf')
                        #response['Content-Disposition'] = 'attachment; filename=somefilename.pdf'
    # Create the PDF object, using the response object as its "file."
			#p = canvas.Canvas(response)

    # Draw things on the PDF. Here's where the PDF generation happens.
    # See the ReportLab documentation for the full list of functionality.
			#p.drawString(100,100,all_code)
			#p.drawImage("/root/scilab_cloud/simple_plot2.png", 100,100, width=500,height=500,mask=None)
			   # Close the PDF object cleanly, and we're done.
			#p.showPage()
			#p.save()
			#return response	
			
			#return render_to_response('default.html',{'input':all_code, 'output':"To be implemented" })
			
		#else:

			split_code = all_code.split()
			#print split_code
			#code = (",".join(split_code)) +  ",quit()"
			plot_filter = re.compile("plot2d\(.*\)")
		 	
			#print split_code[0]
			#print len(split_code)
			variable =[]
			expression = []
			the_data_set = {}
			output = ""
			the_variable = ""
			graphs = []
			for i in range(0,len(split_code)):
				plot_data = plot_filter.findall(split_code[i])
				split_more = split_code[i].split("=")
				#print len(split_more)
				if (len(split_more)>1):
					 
					expression.append(split_more[1])
					evaluated_code = sciscipy.eval(split_code[i])
					the_variable = split_code[i].split("=")[0]
					
					the_variable_value =  sciscipy.read(the_variable)
					the_data_set[the_variable] = the_variable_value
					output = output +str(the_variable) + " =\n " + "    " + str(the_variable_value) + "\n"
					#print split_code[i]
				if plot_data:
				#	print plot_data
					#a=1
					#b=2
					coordinates = plot_data[0].split("(")[1].split(")")[0].split(",")
					x=coordinates[0]
					y=coordinates[1]
						
					pylab.plot(the_data_set[x],the_data_set[y])
		           	        graphs.append('simple_plot' + str(i))
					pylab.savefig(graphs[-1])
			for graph in graphs:

				p = canvas.Canvas(str(graph)+".pdf",pagesize=letter)

                        	#p.drawString(100,100,all_code)
                        	p.drawImage("/root/Downloads/scilab_cloud/"+str(graph)+".png", 1*inch,1*inch, width=5*inch,height=5*inch,mask=None)
                           # Close the PDF object cleanly, and we're done.
                       		p.showPage()
	                   	p.save()

				
				#	print "DONE"
					
				#sciscipy.eval(split_code[i])
				#print sciscipy.read(variable)

				
				
			#cmd = 'scilab -nwni -nb -e \"'+code+'\"'
			#print cmd
			#sciscipy.eval(split_code[0])
			#a = sciscipy.read("a")
			#print a	
			#scilab_evaluated_code = commands.getoutput(cmd)
			return render_to_response('default.html',{'input':all_code,  		'output':output , "graphs":graphs})
        else:
		return render_to_response('default.html',{'input':all_code,'output':"error"})


def some_view(request):
    # Create the HttpResponse object with the appropriate PDF headers.
    response = HttpResponse(mimetype='application/pdf')
    response['Content-Disposition'] = 'attachment; filename=somefilename.pdf'

    # Create the PDF object, using the response object as its "file."
    p = canvas.Canvas(response)

    # Draw things on the PDF. Here's where the PDF generation happens.
    # See the ReportLab documentation for the full list of functionality.
    p.drawString(100, 100, "Hello world.")

    # Close the PDF object cleanly, and we're done.
    p.showPage()
    p.save()
    return response


def download(request,graphname):
	response = HttpResponse(mimetype='application/pdf')
	response['Content-Disposition'] = 'attachment; filename='+str(graphname)+'.pdf'
	p = canvas.Canvas(response)
	p.drawImage("/root/scilab_cloud/"+str(graphname)+".png", 1*inch,1*inch, width=5*inch,height=5*inch,mask=None)
        p.showPage()
 	p.save()
        return response
