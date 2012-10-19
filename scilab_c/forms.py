from django import forms
class ScilabForm(forms.Form):
	scilab_code = forms.TextField(required=True)
    graphicsmode = forms.CheckboxInput()

