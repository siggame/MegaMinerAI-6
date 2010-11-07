deploy:
	gunicorn_django -w 4 -D
stop:
	killall gunicorn_django
clean:
	rm -f *.pyc
	rm -f consumer/*.pyc
	rm -f fwog_web/*.pyc
	rm -f registration/*.pyc

