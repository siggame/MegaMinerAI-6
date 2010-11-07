from django                import forms

class RegistrationCode(forms.Form):
    regCode = forms.CharField()

class SignUp(forms.Form):
    username = forms.CharField()
    password = forms.CharField(widget=forms.PasswordInput)
    password_again = forms.CharField(widget=forms.PasswordInput)
    
    def validate(self, value):
        if value['password1'] != value['password2']:
            raise forms.ValidationError("Password mismatch.")
        print "VALIDATING"
        super(RegistrationCode, self).validate(value)

