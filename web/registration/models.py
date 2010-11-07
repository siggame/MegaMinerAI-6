from django.db import models

class RegistrationCode(models.Model):
    code   = models.CharField(primary_key=True, max_length=20)
    usedBy = models.CharField(null=True, max_length=30)
