创建版本库
1选择合适地方创建一个空目录,确保路径中不要包含有任何中文
mkdir xxx
cd xxx
pwd//用于显示当前目录
2通过git init 命令把这个目录编程git可以管理的仓库
git init//仓库建好，且git可以管理

/*把文件添加到版本库*/
要点：只能跟踪文本文件的改动——图片等二进制只能把文件串起来但北伐跟踪
git add//此命令将添加到git仓库中
git commit --m "this is a"//对版本进行说明

/*时空穿梭机*/
git status//时刻了解仓库状态，如果有修改过可用git diff查看
git diff//再git add 前，先看看改变了哪些东西，方便放心存储
/*版本添加和回退*/

git log
git reset --hard HARD^
git reset --hard 1094a
git reflog//查看以前的ID

工作区和暂存区

cat xxx.txt//显示文档内容的

/*撤销修改*/
这行用于测试——撤销修改

试着推送到 github

/*分支*/
git checkout -b dev//创建dev分支，然后切换dev分支

creating a new branch is quick.

git merge dev//合并分支

git branch -d dev//删除分支

git branch//查看分支
git branch<name>//创建分支
git checkout<name>//切换分支
git checkout -b<name>//创建+切换分支
git merge<name>//合并某分支到当前分支
git branch -d<name>//删除分支

creating a new branch is quick and simple





