from django import forms

class InfoMessage(forms.Form):
    message = forms.CharField(required=False)
    remove  = forms.BooleanField(required=False) 
