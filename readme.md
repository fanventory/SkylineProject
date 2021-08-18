生成倒排索引组
进入pre_process目录
编译命令：g++ main.cpp libleveldb.a -lpthread -I ../../leveldb/include  -o pre_process
执行命令：./pre_process

进入pre_process目录
输出所有的倒排索引组
编译命令：g++ duplicate.cpp libleveldb.a -lpthread -I ../../leveldb/include  -o outputIndex
执行命令：./outputIndex

进入skylineRun目录
运行SPS算法
编译命令：g++ main.cpp libleveldb.a -lpthread -I ../../leveldb/include  -o sps
执行命令：./sps 8187734 10043195 9052829 [-build]
（./sps命令后面接需要查询的关键词数组,第一次执行时需运行-build命令，建立TL_LABEL算法所需索引）

/*
0: 9559683,10480473,9174037,10255305,9922442,8734308,10255298,10879060,10929475,10403506,9833719,8843535,8764046,10131650,10115085,9435273,8815985,9417160,10749032,10802448,8504050,10423587,8984219,11012756,8482629,10907981,8127633,10137916,10293332,10868022,10137910,8648339,10282401,9735749,8227968,9008146,9922090,9046893,
1: 8187734,10250096,8945682,8733693,9565958,8857222,8288375,10734389,8764046,9800485,8817776,10398071,9273738,8902429,8586583,8318606,10907981,9800471,10043195,10288941,10478328,8597810,10332195,9668625,10982786,8532470,10537830,8769993,10142700,10853750,9206513,9922090,10399190,8972123,
2: 9960001,9247624,9816302,8596296,10153903,9731321,8280769,8733693,9517637,9833719,10156254,8648159,9583189,10809198,8764046,8355710,8392989,8815985,10544640,8408278,9253464,10701519,
3: 10723150,10428946,9052829,9559683,10913100,8238219,10687441,8371559,8880624,10424464,8348455,9245162,10518066,8764046,10768331,9072338,9882862,8817776,9574402,10544640,8761468,8648623,8120661,9566890,10907981,9027564,9968668,8960012,10288941,10260544,10332195,9582841,8600938,9928389,10477647,8243397,9752138,8648339,10658305,8109941,9509314,9701319,10858916,8478769,8972123,
4: 9559683,10975956,9437736,9922442,10850504,9186294,8733693,9074606,9786538,10518066,8352228,8817776,10907981,8513488,9252506,9582428,9039266,9583189,9267136,8461451,8648339,8219781,10853750,9747110,9922090,8972123,
5: 8956254,9246838,8238219,10400566,9989512,10573126,10401922,9509396,10949205,10544640,10130326,9731696,10325646,9669703,10332195,10800676,10518299,9582841,9583189,8633639,9668625,10142800,8178911,8648339,8392989,9763910,9279555,10046222,8804910,10255298,9327814,10115278,8817776,8815985,9275666,9922328,8533066,8661703,10399658,8649232,10576274,8564922,10772689,10907981,9118649,9937760,9795659,8624029,9923032,9582428,9639355,8602644,10658305,10117015,9509314,10142700,10939921,9185764,9922090,
*/