from django                import forms
from web.bugtracker.models import Bug

class BugForm(forms.Form):
    subject = forms.CharField()
    description = forms.CharField(widget=forms.Textarea)
    category = forms.ChoiceField(choices=Bug.CATEGORIES)

class BugUpdateForm(forms.Form):
    description = forms.CharField(widget=forms.Textarea)
    category = forms.ChoiceField(choices=Bug.CATEGORIES)
    status = forms.ChoiceField(choices=Bug.STATUSES)

