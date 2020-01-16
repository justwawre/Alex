Using git/gerrit more than 9 months, and git/github more than 12 moths, do a review here.

## data structure of git version database
* The .git folder contains the full version database.
* in git repository, everything is an object, include the file/commit/pointer(including branch,tag) is an object, and every object has a SHA1 reference

### git add <file>
mean add the file into the version database, then return a SHA1
    <img src="git_add.png" width="500" height="200">

### git commit 
* after commit, two object created
    <img src="git_commit_1.png" width="500" height="120">
* one object is new directory structure, another is commit itself
    <img src="git_commit_2.png" width="500" height="120">
* can verify by
    <img src="git_commit_3.png" width="500" height="50">
* every commit is a full snapshot of the whole project
    <img src="git_commit_4.png" width="500" height="250">
### git commit --amend 
create a sibling node, instead of child node, in the version history tree.


## distributed
When using the clearcase/svn before, I had rename filename as file_1.c file_2.c, to record the version locally. Now Git is a fully version control system which can run locally.

## data compression
* non-modified file will not dupliacted
* only delta was sent between the local/remote repository
    <img src="git_push.png" width="500" height="250">
## Gerrit
* it a git server with access control
* allows to review commits before they are integrated into a target branch.
* built on top of Git
### push for review
* refer to remote branch
    <img src="gerrit_push_review.png" width="500" height="250">
* it generate change/patch set
    <img src="gerrit_change.png" width="500" height="300">
* the change-id was generated and inserted into commit message by the commit hook
* Gerrit whill create whether change existed or not, then updte patchset or create a change

## CI/CD behind gerrit
Jenkins

## reference
* google: git/gerrit presentation
