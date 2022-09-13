
@echo off

echo "Start pulling the latest code"
git pull origin master
echo "Add code to the staging area"
git add .
echo "Commit the staging area to the local repository"

set  /p a="Input commit: "

git commit -m %a%
echo "Push local code to the remote repository"
git push origin master

echo "Press any key to end." & pause > nul
