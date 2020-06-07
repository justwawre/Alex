<!-- pagebreak -->
# SP13 req2 优化

got: https://gerrit.ericsson.se/#/c/5875778/

code:
upc/ulMacCeBl/schedCtrlSwU/src/ulmacce_schedctrl_tdrfo.c

test case:
tdrFoTests:tdrFo_ts_ulValidateInfoInd

进一步优化方法： 类似归并排序序
1.  对每一个validator 取得的数据（应该不到50），先按cell id 进行排序
2.  排序后的数据写到 se_array[] 中，记录该validator 的 index_start, total_of_se
3.  重复 step 1, step 2，将所有validator 的输出，都放到se_array[]中，并且得到一张validator_info[] 的表
4.  按cell id, 先到  validator_info[] 中取到每个validator 的 index_start, total_of_se
5.  然后根据它在se_array[] 中 找到该cell id 的se,记录 count_of_se 到validator_info[] 
6.  如果该cell id  sum (count_of_se) 不为0， 申请CM, 然后复制，发送signal
7.  重复 step 4/5/6


# 原来雷亮的方案
用一巨大的辅助空间,将所有的数据排序到se_array[]
还增加一管理信息数组admin[cellid],记录该cellid 的数据在 se_array[]中的起点和长度
需要时直接copy 到cm