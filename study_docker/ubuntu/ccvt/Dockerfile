FROM python:3.5

RUN apt-get update 
RUN  pip install oss2 
RUN  pip install django && pip install wxpy
RUN cd /robot && python manage.py runserver
Run git clone https://github.com/AlphaSunny/robot.git

CMD ["/bin/bash"]