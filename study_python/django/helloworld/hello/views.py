from django.shortcuts import render

# Create your views here.
from django.http import HttpResponse
from wxpy import *

def index(request):
    return HttpResponse("hello world")

def time(request):
    return  HttpResponse("12:00:00")

def robot(request):
    return HttpResponse("Robot start")