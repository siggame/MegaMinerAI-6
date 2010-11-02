#
# Begins the update server, db manager, and a tentale on the localhost
#
python db.py > /dev/null 2>&1  &
cd update
python update.py > /dev/null 2>&1 &
cd ../tentacle
python tentacle.py > /dev/null 2>&1 & 
exit 0
