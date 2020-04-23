# Copyright 2018  Alex(xuyc@sina.com).
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0
#投资人，基金经理的初始投入
invest_0, manager_0 = 10000, 0


def emulate(inc_list, commission_rate, manfee_rate, bInvest):
    invest, manager = invest_0, manager_0
    print("本期收益\t投资者帐户\t经理帐户\t管理费")
    print("%8s%16d%16d" % ('', invest_0, manager_0), sep="")

    investor_peak = invest_0  # 采用高水位法
    for inc in inc_list:
        #管理费在期初计提，假设基金经理即使跟投，也不提管理费
        man_fee = round(invest*manfee_rate, 2)
        invest_revenue = round(invest * inc, 2)
        invest = round(invest + invest_revenue-man_fee, 2)
        if invest > investor_peak:
            commission = round((invest-investor_peak) * commission_rate, 2)
            invest -= commission
            investor_peak = invest
        else:
            commission = 0

        if bInvest:
            manager = round(manager*(1+inc) + commission, 2)
        else:
            manager = round(manager + commission, 2)

        print("%8d%16d%16d%16d" % (invest_revenue, invest, manager, man_fee), sep="")

    investor_earn = invest-invest_0
    manager_earn = manager-manager_0
    ratio_percent = round(100*manager_earn/(manager_earn+investor_earn), 2)
    print("管理费：", manfee_rate*100, "%     提成：", commission_rate*100,
          "%  基金经理再投入：", bInvest, "  所得/总收益:", ratio_percent, "%\n", sep='')


ll = [0.1, 0.5, 0.3, -0.1, 0, 0.2]  # 每个提成周期的增长率
emulate(ll, 0.2, 0.0, False)
emulate(ll, 0.2, 0.01, False)
emulate(ll, 0.2, 0.01, True)
