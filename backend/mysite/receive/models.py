from django.db import models

# Create your models here.

class ProgramList(models.Model) :
    name = models.CharField(max_length=20)
    msg = models.TextField(max_length=500)