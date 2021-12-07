from django.urls import path
from receive.views import mainfunc,addprog,getprog

urlpatterns = [
    path('run' ,mainfunc),
    path('addprog' , addprog),
    path('getprog' , getprog)
]
