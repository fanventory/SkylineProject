## 处理强连通分量
进入Digraph目录：cd Digraph<br>
编译命令：g++ main.cpp -o kosa
执行命令：./kosa

## 生成倒排索引组
进入pre_process目录：cd pre_process<br>
编译命令：g++ main.cpp libleveldb.a -lpthread -I ../../leveldb/include  -o pre_process<br>
执行命令：./pre_process

## 进入pre_process目录:cd pre_process
输出所有的倒排索引组<br>
编译命令：g++ duplicate.cpp libleveldb.a -lpthread -I ../../leveldb/include  -o outputIndex<br>
执行命令：./outputIndex

## 进入skylineRun目录:cd skylineRun
运行SPS算法<br>
编译命令：g++ main.cpp libleveldb.a -lpthread -I ../../leveldb/include  -o sps<br>
执行命令：./sps 8187734 10043195 9052829 [-build]<br>
（./sps命令后面接需要查询的关键词数组,第一次执行时需运行-build命令，建立TL_LABEL算法所需索引）

## 部分关键词
0: 9559683,10480473,9174037,10255305,9922442,8734308,10255298,10879060,10929475,10403506,9833719,8843535,8764046,10131650,10115085,9435273,8815985,9417160,10749032,10802448,8504050,10423587,8984219,11012756,8482629,10907981,8127633,10137916,10293332,10868022,10137910,8648339,10282401,9735749,8227968,9008146,9922090,9046893,<br>
1: 8187734,10250096,8945682,8733693,9565958,8857222,8288375,10734389,8764046,9800485,8817776,10398071,9273738,8902429,8586583,8318606,10907981,9800471,10043195,10288941,10478328,8597810,10332195,9668625,10982786,8532470,10537830,8769993,10142700,10853750,9206513,9922090,10399190,8972123,<br>
2: 9960001,9247624,9816302,8596296,10153903,9731321,8280769,8733693,9517637,9833719,10156254,8648159,9583189,10809198,8764046,8355710,8392989,8815985,10544640,8408278,9253464,10701519,<br>
3: 10723150,10428946,9052829,9559683,10913100,8238219,10687441,8371559,8880624,10424464,8348455,9245162,10518066,8764046,10768331,9072338,9882862,8817776,9574402,10544640,8761468,8648623,8120661,9566890,10907981,9027564,9968668,8960012,10288941,10260544,10332195,9582841,8600938,9928389,10477647,8243397,9752138,8648339,10658305,8109941,9509314,9701319,10858916,8478769,8972123,<br>
4: 9559683,10975956,9437736,9922442,10850504,9186294,8733693,9074606,9786538,10518066,8352228,8817776,10907981,8513488,9252506,9582428,9039266,9583189,9267136,8461451,8648339,8219781,10853750,9747110,9922090,8972123,<br>
5: 8956254,9246838,8238219,10400566,9989512,10573126,10401922,9509396,10949205,10544640,10130326,9731696,10325646,9669703,10332195,10800676,10518299,9582841,9583189,8633639,9668625,10142800,8178911,8648339,8392989,9763910,9279555,10046222,8804910,10255298,9327814,10115278,8817776,8815985,9275666,9922328,8533066,8661703,10399658,8649232,10576274,8564922,10772689,10907981,9118649,9937760,9795659,8624029,9923032,9582428,9639355,8602644,10658305,10117015,9509314,10142700,10939921,9185764,9922090,


## 部分关键词neo4j查询
1. 8187734 10043195 9052829
> 结点1<br>
match
(a:KEYWORD{id:'8187734'}),
(b:KEYWORD{id:'10043195'}),
(c:KEYWORD{id:'9052829'}),
(d:NODE{id:'1'}),
p1=(d)-[*1..2]->(a),
p2=(d)-[*1..2]->(b),
p3=(d)-[*1..3]->(c) 
return p1,p2,p3

> 结点581411<br>
match
(a:KEYWORD{id:'8187734'}),
(b:KEYWORD{id:'10043195'}),
(c:KEYWORD{id:'9052829'}),
(d:NODE{id:'581411'}),
p1=(d)-[*1..4]->(a),
p2=(d)-[*1..2]->(b),
p3=(d)-[*1..2]->(c) 
return p1,p2,p3

2. 8372233 8203852 9572255
> 结点792554<br>
match
(n:NODE{id:'792554'}),
(a1:NODE{id:'4835'}),
(a2:NODE{id:'1020456'}),
(a3:NODE{id:'889803'}),
(a4:NODE{id:'2792140'}),
(a5:NODE{id:'5849790'}),
(a6:NODE{id:'5314351'}),
(a7:NODE{id:'5410769'}),
(a8:NODE{id:'3333178'}),
(a9:NODE{id:'7995231'}),
(a10:KEYWORD{id:'8203852'}),
(b2:NODE{id:'7298658'}),
(b3:NODE{id:'6139648'}),
(b4:NODE{id:'3119038'}),
(b5:NODE{id:'7755421'}),
(b6:NODE{id:'6057002'}),
(b7:NODE{id:'35923'}),
(b8:NODE{id:'390355'}),
(b9:NODE{id:'730755'}),
(b10:NODE{id:'5549226'}),
(b11:KEYWORD{id:'8372233'}),
(c1:KEYWORD{id:'9572255'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_NODE]->(a9)-[:NODE_KEYWORD]->(a10),
p2=(a1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_NODE]->(b8)-[:NODE_NODE]->(b9)-[:NODE_NODE]->(b10)-[:NODE_KEYWORD]->(b11),
p3=(n)-[:NODE_KEYWORD]->(c1)
return p1,p2,p3

3. 9862503 9983121 10993170
> 结点575392<br>
match
(n:NODE{id:'575392'}),
(a1:NODE{id:'6934192'}),
(a2:NODE{id:'4692324'}),
(a3:NODE{id:'115811'}),
(a4:NODE{id:'824743'}),
(a5:NODE{id:'1721659'}),
(a6:NODE{id:'8070338'}),
(a7:NODE{id:'674675'}),
(a8:NODE{id:'1807283'}),
(a9:NODE{id:'121878'}),
(a10:KEYWORD{id:'9862503'}),
(b2:NODE{id:'8031394'}),
(b3:NODE{id:'5177567'}),
(b4:NODE{id:'6930815'}),
(b5:NODE{id:'6855364'}),
(b6:NODE{id:'6257590'}),
(b7:NODE{id:'407558'}),
(b8:NODE{id:'820723'}),
(b9:NODE{id:'431487'}),
(b10:NODE{id:'756009'}),
(b11:NODE{id:'315248'}),
(b12:NODE{id:'161662'}),
(b13:KEYWORD{id:'10993170'}),
(c1:KEYWORD{id:'9983121'}),
(c2:NODE{id:'7515550'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_NODE]->(a9)-[:NODE_KEYWORD]->(a10),
p2=(a1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_NODE]->(b8)-[:NODE_NODE]->(b9)-[:NODE_NODE]->(b10)-[:NODE_NODE]->(b11)-[:NODE_NODE]->(b12)-[:NODE_KEYWORD]->(b13),
p3=(a2)-[:NODE_KEYWORD]->(c1),
p4=(b2)-[:NODE_KEYWORD]->(c1),
p5=(a1)-[:NODE_NODE]->(c2)-[:NODE_KEYWORD]->(c1)
return p1,p2,p3,p4,p5

> 结点872913<br>
match
(n:NODE{id:'872913'}),
(a1:NODE{id:'6934192'}),
(a2:NODE{id:'4692324'}),
(a3:NODE{id:'115811'}),
(a4:NODE{id:'824743'}),
(a5:NODE{id:'1721659'}),
(a6:NODE{id:'8070338'}),
(a7:NODE{id:'674675'}),
(a8:NODE{id:'1807283'}),
(a9:NODE{id:'121878'}),
(a10:KEYWORD{id:'9862503'}),
(b2:NODE{id:'8031394'}),
(b3:NODE{id:'5177567'}),
(b4:NODE{id:'6930815'}),
(b5:NODE{id:'6855364'}),
(b6:NODE{id:'6257590'}),
(b7:NODE{id:'407558'}),
(b8:NODE{id:'820723'}),
(b9:NODE{id:'431487'}),
(b10:NODE{id:'756009'}),
(b11:NODE{id:'315248'}),
(b12:NODE{id:'161662'}),
(b13:KEYWORD{id:'10993170'}),
(c1:KEYWORD{id:'9983121'}),
(c2:NODE{id:'7515550'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_NODE]->(a9)-[:NODE_KEYWORD]->(a10),
p2=(a1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_NODE]->(b8)-[:NODE_NODE]->(b9)-[:NODE_NODE]->(b10)-[:NODE_NODE]->(b11)-[:NODE_NODE]->(b12)-[:NODE_KEYWORD]->(b13),
p3=(a2)-[:NODE_KEYWORD]->(c1),
p4=(b2)-[:NODE_KEYWORD]->(c1),
p5=(a1)-[:NODE_NODE]->(c2)-[:NODE_KEYWORD]->(c1)
return p1,p2,p3,p4,p5

> 结点380487<br>
match
(n:NODE{id:'380487'}),
(a1:NODE{id:'863692'}),
(a2:NODE{id:'412448'}),
(a3:NODE{id:'5120077'}),
(a4:NODE{id:'5768451'}),
(a5:NODE{id:'674675'}),
(a6:NODE{id:'1807283'}),
(a7:NODE{id:'121878'}),
(a8:KEYWORD{id:'9862503'}),
(b1:NODE{id:'2184577'}),
(b2:NODE{id:'2608222'}),
(b3:NODE{id:'5177567'}),
(b4:NODE{id:'6930815'}),
(b5:NODE{id:'6855364'}),
(b6:NODE{id:'6257590'}),
(b7:NODE{id:'407558'}),
(b8:NODE{id:'820723'}),
(b9:NODE{id:'431487'}),
(b10:NODE{id:'756009'}),
(b11:NODE{id:'315248'}),
(b12:NODE{id:'161662'}),
(b13:KEYWORD{id:'10993170'}),
(c1:NODE{id:'5589460'}),
(c2:NODE{id:'6934192'}),
(c3:NODE{id:'8031394'}),
(c4:NODE{id:'7515550'}),
(c5:NODE{id:'4692324'}),
(c6:KEYWORD{id:'9983121'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_KEYWORD]->(a8),
p2=(n)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_NODE]->(b8)-[:NODE_NODE]->(b9)-[:NODE_NODE]->(b10)-[:NODE_NODE]->(b11)-[:NODE_NODE]->(b12)-[:NODE_KEYWORD]->(b13),
p3=(n)-[:NODE_NODE]->(c1)-[:NODE_NODE]->(c2)-[:NODE_NODE]->(c3)-[:NODE_KEYWORD]->(c6),
p4=(c2)-[:NODE_NODE]->(c4)-[:NODE_KEYWORD]->(c6),
p5=(c2)-[:NODE_NODE]->(c5)-[:NODE_KEYWORD]->(c6)
return p1,p2,p3,p4,p5

4. 8334781 8396032 9590953
> 结点188065<br>
match
(n:NODE{id:'188065'}),
(a1:NODE{id:'416351'}),
(a2:NODE{id:'7247403'}),
(a3:NODE{id:'824743'}),
(a4:NODE{id:'5205596'}),
(a5:NODE{id:'154670'}),
(a6:NODE{id:'1352052'}),
(a7:NODE{id:'7579702'}),
(a8:NODE{id:'4205202'}),
(a9:KEYWORD{id:'8396032'}),
(b1:NODE{id:'2824615'}),
(b2:NODE{id:'419694'}),
(b3:NODE{id:'1041441'}),
(b4:NODE{id:'1109959'}),
(b5:NODE{id:'759127'}),
(b6:NODE{id:'7980831'}),
(b7:NODE{id:'6762757'}),
(b8:KEYWORD{id:'9590953'}),
(c1:KEYWORD{id:'8334781'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_KEYWORD]->(a9),
p2=(a1)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_KEYWORD]->(b8),
p3=(n)-[:NODE_KEYWORD]->(c1)
return p1,p2,p3

> 结点579145<br>
match
(n:NODE{id:'579145'}),
(a1:NODE{id:'21693'}),
(a2:NODE{id:'1215945'}),
(a3:NODE{id:'4515603'}),
(a4:NODE{id:'3648095'}),
(a5:NODE{id:'6071270'}),
(a6:NODE{id:'726734'}),
(a7:NODE{id:'4447314'}),
(a8:NODE{id:'799045'}),
(a9:KEYWORD{id:'8334781'}),
(b1:NODE{id:'3960336'}),
(b2:NODE{id:'2722175'}),
(b3:NODE{id:'6397852'}),
(b4:NODE{id:'1068713'}),
(b5:NODE{id:'1352052'}),
(b6:NODE{id:'7579702'}),
(b7:NODE{id:'4205202'}),
(b8:KEYWORD{id:'8396032'}),
(c1:NODE{id:'4104475'}),
(c2:NODE{id:'6762757'}),
(c3:KEYWORD{id:'9590953'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_KEYWORD]->(a9),
p2=(c1)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_KEYWORD]->(b8),
p3=(n)-[:NODE_NODE]->(c1)-[:NODE_NODE]->(c2)-[:NODE_KEYWORD]->(c3)
return p1,p2,p3

> 结点639834<br>
match
(n:NODE{id:'639834'}),
(a1:NODE{id:'321860'}),
(a2:NODE{id:'21693'}),
(a3:NODE{id:'1215945'}),
(a4:NODE{id:'4515603'}),
(a5:NODE{id:'3648095'}),
(a6:NODE{id:'6071270'}),
(a7:NODE{id:'726734'}),
(a8:NODE{id:'4447314'}),
(a9:NODE{id:'799045'}),
(a10:KEYWORD{id:'8334781'}),
(b1:NODE{id:'3960336'}),
(b2:NODE{id:'1602712'}),
(b3:NODE{id:'6514203'}),
(b4:NODE{id:'4656309'}),
(b5:NODE{id:'7685531'}),
(b6:NODE{id:'6762757'}),
(b7:KEYWORD{id:'9590953'}),
(c1:KEYWORD{id:'8396032'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_NODE]->(a9)-[:NODE_KEYWORD]->(a10),
p2=(a1)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_KEYWORD]->(b7),
p3=(n)-[:NODE_KEYWORD]->(c1)
return p1,p2,p3

> 结点799045<br>
match
(n:NODE{id:'799045'}),
(a1:NODE{id:'416351'}),
(a2:NODE{id:'7247403'}),
(a3:NODE{id:'824743'}),
(a4:NODE{id:'5205596'}),
(a5:NODE{id:'154670'}),
(a6:NODE{id:'1352052'}),
(a7:NODE{id:'7579702'}),
(a8:NODE{id:'4205202'}),
(a9:KEYWORD{id:'8396032'}),
(b1:NODE{id:'2824615'}),
(b2:NODE{id:'419694'}),
(b3:NODE{id:'1041441'}),
(b4:NODE{id:'1109959'}),
(b5:NODE{id:'759127'}),
(b6:NODE{id:'7980831'}),
(b7:NODE{id:'6762757'}),
(b8:KEYWORD{id:'9590953'}),
(c1:KEYWORD{id:'8334781'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_KEYWORD]->(a9),
p2=(a1)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_KEYWORD]->(b8),
p3=(n)-[:NODE_KEYWORD]->(c1)
return p1,p2,p3

> 结点423909<br>
match
(n:NODE{id:'423909'}),
(a1:NODE{id:'1425948'}),
(a2:NODE{id:'4358117'}),
(a3:NODE{id:'7926646'}),
(a4:NODE{id:'3922156'}),
(a5:NODE{id:'6581455'}),
(a6:NODE{id:'799045'}),
(a7:KEYWORD{id:'8334781'}),
(b1:NODE{id:'6331224'}),
(b2:NODE{id:'1700760'}),
(b3:NODE{id:'4926167'}),
(b4:NODE{id:'7879801'}),
(b5:NODE{id:'7579702'}),
(b6:NODE{id:'4205202'}),
(b7:KEYWORD{id:'8396032'}),
(c1:NODE{id:'759127'}),
(c2:NODE{id:'7980831'}),
(c3:NODE{id:'6762757'}),
(c4:KEYWORD{id:'9590953'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_KEYWORD]-(a7),
p2=(a1)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_KEYWORD]->(b7),
p3=(n)-[:NODE_NODE]->(c1)-[:NODE_NODE]->(c2)-[:NODE_NODE]->(c3)-[:NODE_KEYWORD]->(c4)
return p1,p2,p3

> 结点226758<br>
match
(n:NODE{id:'226758'}),
(a1:NODE{id:'2783598'}),
(a2:NODE{id:'772980'}),
(a3:NODE{id:'6394505'}),
(a4:NODE{id:'2382636'}),
(a5:NODE{id:'6268150'}),
(a6:NODE{id:'185458'}),
(a7:NODE{id:'745312'}),
(a8:NODE{id:'799045'}),
(a9:KEYWORD{id:'8334781'}),
(b1:NODE{id:'1106300'}),
(b2:NODE{id:'7579702'}),
(b3:NODE{id:'4205202'}),
(b4:KEYWORD{id:'8396032'}),
(c1:NODE{id:'1041441'}),
(c2:NODE{id:'1109959'}),
(c3:NODE{id:'759127'}),
(c4:NODE{id:'7980831'}),
(c5:NODE{id:'6762757'}),
(c6:KEYWORD{id:'9590953'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_KEYWORD]->(a9),
p2=(n)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_KEYWORD]->(b4),
p3=(n)-[:NODE_NODE]->(c1)-[:NODE_NODE]->(c2)-[:NODE_NODE]->(c3)-[:NODE_NODE]->(c4)-[:NODE_NODE]->(c5)-[:NODE_KEYWORD]->(c6)
return p1,p2,p3

5. 8689980 10038054 10547090
> 结点10392<br>
match
(n:NODE{id:'10392'}),
(a1:NODE{id:'458604'}),
(a2:NODE{id:'1263303'}),
(a3:NODE{id:'7657314'}),
(a4:NODE{id:'3288058'}),
(a5:NODE{id:'1783768'}),
(a6:NODE{id:'1754524'}),
(a7:NODE{id:'4324042'}),
(a8:NODE{id:'5020595'}),
(a9:NODE{id:'4616567'}),
(a10:NODE{id:'1707756'}),
(a11:KEYWORD{id:'8689980'}),
(b1:NODE{id:'629838'}),
(b2:NODE{id:'553713'}),
(b3:NODE{id:'2837715'}),
(b4:NODE{id:'4432637'}),
(b5:NODE{id:'7558677'}),
(b6:NODE{id:'8032034'}),
(b7:NODE{id:'2101091'}),
(b8:NODE{id:'3894507'}),
(b9:NODE{id:'1661047'}),
(b10:NODE{id:'2738599'}),
(b11:NODE{id:'2737964'}),
(b12:NODE{id:'1991142'}),
(b13:NODE{id:'6783105'}),
(b14:NODE{id:'6400316'}),
(b15:NODE{id:'4421810'}),
(b16:NODE{id:'5221771'}),
(b17:NODE{id:'1091576'}),
(b18:NODE{id:'3380702'}),
(b19:NODE{id:'6906835'}),
(b20:NODE{id:'7962109'}),
(b21:NODE{id:'5386714'}),
(b22:NODE{id:'5689716'}),
(b23:NODE{id:'5508397'}),
(b24:KEYWORD{id:'10038054'}),
(c1:KEYWORD{id:'10547090'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_NODE]->(a9)-[:NODE_NODE]->(a10)-[:NODE_KEYWORD]->(a11),
p2=(a1)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_NODE]->(b8)-[:NODE_NODE]->(b9)-[:NODE_NODE]->(b10)-[:NODE_NODE]->(b11)-[:NODE_NODE]->(b12)-[:NODE_NODE]->(b13)-[:NODE_NODE]->(b14)-[:NODE_NODE]->(b15)-[:NODE_NODE]->(b16)-[:NODE_NODE]->(b17)-[:NODE_NODE]->(b18)-[:NODE_NODE]->(b19)-[:NODE_NODE]->(b20)-[:NODE_NODE]->(b21)-[:NODE_NODE]->(b22)-[:NODE_NODE]->(b23)-[:NODE_KEYWORD]->(b24),
p3=(n)-[:NODE_KEYWORD]->(c1)
return p1,p2,p3

> 结点203460<br>
match
(n:NODE{id:'203460'}),
(a1:NODE{id:'471196'}),
(a2:NODE{id:'1744559'}),
(a3:NODE{id:'4535828'}),
(a4:NODE{id:'1783768'}),
(a5:NODE{id:'1754524'}),
(a6:NODE{id:'4324042'}),
(a7:NODE{id:'5020595'}),
(a8:NODE{id:'4616567'}),
(a9:NODE{id:'1707756'}),
(a10:KEYWORD{id:'8689980'}),
(b1:NODE{id:'6662439'}),
(b2:NODE{id:'1073773'}),
(b3:NODE{id:'2961145'}),
(b4:NODE{id:'4314984'}),
(b5:NODE{id:'275882'}),
(b6:NODE{id:'469289'}),
(b7:NODE{id:'4734620'}),
(b8:NODE{id:'3894507'}),
(b9:NODE{id:'1661047'}),
(b10:NODE{id:'2738599'}),
(b11:NODE{id:'2737964'}),
(b12:NODE{id:'1991142'}),
(b13:NODE{id:'6783105'}),
(b14:NODE{id:'6400316'}),
(b15:NODE{id:'4421810'}),
(b16:NODE{id:'5221771'}),
(b17:NODE{id:'1091576'}),
(b18:NODE{id:'3380702'}),
(b19:NODE{id:'6906835'}),
(b20:NODE{id:'7962109'}),
(b21:NODE{id:'5386714'}),
(b22:NODE{id:'5689716'}),
(b23:NODE{id:'5508397'}),
(b24:KEYWORD{id:'10038054'}),
(c1:KEYWORD{id:'10547090'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_NODE]->(a9)-[:NODE_KEYWORD]->(a10),
p2=(a3)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_NODE]->(b8)-[:NODE_NODE]->(b9)-[:NODE_NODE]->(b10)-[:NODE_NODE]->(b11)-[:NODE_NODE]->(b12)-[:NODE_NODE]->(b13)-[:NODE_NODE]->(b14)-[:NODE_NODE]->(b15)-[:NODE_NODE]->(b16)-[:NODE_NODE]->(b17)-[:NODE_NODE]->(b18)-[:NODE_NODE]->(b19)-[:NODE_NODE]->(b20)-[:NODE_NODE]->(b21)-[:NODE_NODE]->(b22)-[:NODE_NODE]->(b23)-[:NODE_KEYWORD]->(b24),
p3=(n)-[:NODE_KEYWORD]->(c1)
return p1,p2,p3

> 结点714287<br>
match
(n:NODE{id:'714287'}),
(a1:NODE{id:'1021104'}),
(a2:NODE{id:'6174938'}),
(a3:NODE{id:'7261367'}),
(a4:NODE{id:'1783768'}),
(a5:NODE{id:'1754524'}),
(a6:NODE{id:'4324042'}),
(a7:NODE{id:'5020595'}),
(a8:NODE{id:'4616567'}),
(a9:NODE{id:'1707756'}),
(a10:KEYWORD{id:'8689980'}),
(b2:NODE{id:'253979'}),
(b3:NODE{id:'2012146'}),
(b4:NODE{id:'395705'}),
(b5:NODE{id:'5796352'}),
(b6:NODE{id:'1814604'}),
(b7:NODE{id:'6683028'}),
(b8:NODE{id:'8032034'}),
(b9:NODE{id:'2101091'}),
(b10:NODE{id:'3894507'}),
(b11:NODE{id:'1661047'}),
(b12:NODE{id:'2738599'}),
(b13:NODE{id:'2737964'}),
(b14:NODE{id:'1991142'}),
(b15:NODE{id:'6783105'}),
(b16:NODE{id:'6400316'}),
(b17:NODE{id:'4421810'}),
(b18:NODE{id:'5221771'}),
(b19:NODE{id:'1091576'}),
(b20:NODE{id:'3380702'}),
(b21:NODE{id:'6906835'}),
(b22:NODE{id:'7962109'}),
(b23:NODE{id:'5386714'}),
(b24:NODE{id:'5689716'}),
(b25:NODE{id:'5508397'}),
(b26:KEYWORD{id:'10038054'}),
(c1:NODE{id:'7746776'}),
(c2:KEYWORD{id:'10547090'}),
p1=(n)-[:NODE_NODE]->(a1)-[:NODE_NODE]->(a2)-[:NODE_NODE]->(a3)-[:NODE_NODE]->(a4)-[:NODE_NODE]->(a5)-[:NODE_NODE]->(a6)-[:NODE_NODE]->(a7)-[:NODE_NODE]->(a8)-[:NODE_NODE]->(a9)-[:NODE_KEYWORD]->(a10),
p2=(n)-[:NODE_NODE]->(b1)-[:NODE_NODE]->(b2)-[:NODE_NODE]->(b3)-[:NODE_NODE]->(b4)-[:NODE_NODE]->(b5)-[:NODE_NODE]->(b6)-[:NODE_NODE]->(b7)-[:NODE_NODE]->(b8)-[:NODE_NODE]->(b9)-[:NODE_NODE]->(b10)-[:NODE_NODE]->(b11)-[:NODE_NODE]->(b12)-[:NODE_NODE]->(b13)-[:NODE_NODE]->(b14)-[:NODE_NODE]->(b15)-[:NODE_NODE]->(b16)-[:NODE_NODE]->(b17)-[:NODE_NODE]->(b18)-[:NODE_NODE]->(b19)-[:NODE_NODE]->(b20)-[:NODE_NODE]->(b21)-[:NODE_NODE]->(b22)-[:NODE_NODE]->(b23)-[:NODE_NODE]->(b24)-[:NODE_NODE]->(b25)-[:NODE_KEYWORD]->(b26),
p3=(n)-[:NODE_NODE]->(c1)-[:NODE_KEYWORD]->(c2)
return p1,p2,p3

