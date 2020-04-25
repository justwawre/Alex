
由于UNIX被Linux取代，当初看的，写的code，现在已经不太重要,所以大部分就删掉了。

# nice()  don't work in multi cpu arch

before, in my own CentOS pc, the nice don't work, in WSL, the same situation.
* the child process nice valued modified, but the scheduling was not affected
* using top -H 看，nice 
* lscpu to check
   
 Alex:应该是多核cpu下，由于两个process运行在不同的core上，nice() 已经没有什么意义。




