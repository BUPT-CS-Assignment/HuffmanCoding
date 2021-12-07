from django.db import models

from django.http import JsonResponse
from django.db.models import F
from django.db import IntegrityError, transaction
from receive.models import ProgramList

import json,traceback

from django.core.paginator import Paginator, EmptyPage

import os

from django.utils.regex_helper import contains

def mainfunc(request):
    try : 
        print("This request from : " , request.META['REMOTE_ADDR'] )
        info = request.POST
        id = info['id']
        type = info['type']
        content = info['content']
        if id == '1' :
            id = '0'

        with open(f'./receive/program/{id}/in.txt' , 'w' ,encoding='utf-8') as file:
            file.write(content)
            file.close()
        if type == 'encode' :
            os.system(f'cd receive\program\{id} & {id}.exe 0')
        elif type == 'decode':
            os.system(f'cd receive\program\{id} & {id}.exe 1')
        try :
            with open(f'./receive/program/{id}/out.txt' , 'r' ,encoding='utf-8') as file:
                content = file.read()
                file.close()
        except Exception:
            return JsonResponse({'ret': 2, 'msg':'There are some errs on this test program'})
        #10.21.220.218
        if(content == '') :
            return JsonResponse({'ret': 1 ,  'msg':'Invalid Input!'})

        return JsonResponse({'ret': 0 ,  'msg':'Success!' , 'content' :f'{content}'})
    except Exception :
        traceback.format_exc()
        return JsonResponse({'ret': -1, 'msg':f'未知错误{traceback.format_exc()}'})


def addprog(request) :
    try : 
        info = request.POST
        try :
            ProgramList.objects.get(name=info['name'])
        except ProgramList.DoesNotExist :
            with transaction.atomic():
                new_prog = ProgramList.objects.create(
                    name = info['name'],
                    msg = info['msg'],
                )
                content = request.FILES.get('file')
                FILE_PATH = f'./receive/program/{new_prog.id}'
                if os.path.exists(FILE_PATH) is False:
                    os.mkdir(FILE_PATH)

                FILE_PATH += f'/{new_prog.id}.exe'
                with open(FILE_PATH , 'wb+') as file:
                    for chunk in content.chunks():
                        file.write(chunk)
                    file.close()
                new_prog.save()
                return JsonResponse({'ret': 0 ,  'msg':'Success!' })
        
        return JsonResponse({'ret': 1, 'msg':'Sorry,Existed!'})


    except Exception :
        return JsonResponse({'ret': -1, 'msg':f'Unknow Err...{traceback.format_exc()}'})


def getprog(request):
    try:
        print("This request from ：" , request.META['REMOTE_ADDR'])
        qs = ProgramList.objects.values()
        qs = list(qs)
        return JsonResponse({'ret': 0, 'retlist': qs})
    except EmptyPage:
        return JsonResponse({'ret': 0, 'msg' :'Empty'})
    except:
        return JsonResponse({'ret': 1, 'msg' : f'Error{traceback.format_exc()}'})
