
###plcopen_motion_control-master
from: https://github.com/leijian001/plcopen_motion_control
  only for study
  
cmake .. -DPLOT=On -DTEST=On -DDEBUG=On

./test/planner_test --gtest_filter=PlannerTest.VelocityUp
./test/function_block_test  --gtest_filter=FunctionBlockTest.MC_MoveVelocity


/* */
  去掉ruckig  //使用新的ruckig 后编译出错，应该是ruckig接口更新了。
  使用 pybind11 调用plot 画图。
  type_ 初始化为Online 测试出错。
