# Setup guide for QT #
1)Install creator [here](https://www.qt.io/download-qt-installer)

2)Proceed by installer steps normally

3)In the custom installation menu go to default setup and select *qt 5.15.2*. 

After that deselect: 
*	*MSVC 2015*
*	*all UWP*
*	*virtual keyboard*
*	*web engine*
*	*debug information files*

4)Finish installation normally

# Setup guide for Git #
If you alraedy have *git bash* installed, skip this block

1)Download installer [here](https://git-scm.com/download/win)

2)Launch installer

3)Proceed by installer steps normally, you can leave parameters default or change them if you know what are you doing

4)On the _select components_ step check that *Windows Explorer integration* -> *Git Bash Here* is selected

5)Finish installation normally

# Get revision on your computer #

1) Create void directory where you plan to locate repository
2) Click right mouse button and select *Git Bash Here*
3) Run this commands (one by one)  
```
git clone https://github.com/HellInsider/Shopping-Mall-Maps.git
cd Shopping-Mall-Maps/
git config --global user.email "your_email_with_github_account@example.com"
git config --global user.name "YourGitHubUsername"
git checkout develop
get pull
```
4) Run QT Creator and select *File*->*Open File or Project*->*your_path_to_repository\Shopping-Mall-Maps\code\allmall.pro*

### If you have problem with any step, contact [me](https://t.me/PlankaPalenkova) in telegram  ###
