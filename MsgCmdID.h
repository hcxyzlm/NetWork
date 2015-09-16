#ifndef _MSG_CMD_ID_H_
#define _MSG_CMD_ID_H_

const int PROC_VER = 102010;//协议版本

const int MSG_OPTION_STR		=			1;    //协议发送的为字符串
const int MSG_OPTION_PROTO		=			2;    //协议发送的为protobuf


/////////////////////////login///////////////////////
const int CMD_ID_LOGIN			=			100;         //登录协议
const int CMD_ID_LOGINOUT		=			101;		 //登出
const int CMD_ID_USER_INFO		=			102;         //用户信息

const int CMD_ID_ALIVE			=			105;		 //心跳协议
const int CMD_ID_NEWER_GIVE		=			106;		 //新玩家赠送	
const int CMD_ID_RUIN_PROTECT	=			107;		 //每日赠送
const int CMD_ID_SELF_PROP_LIST =			108;		//自己的道具列表
const int CMD_ID_USE_PROP		=			109;		//使用自己的道具
const int CMD_ID_SALE_ITEM		=			110;		//卖掉道具
const int CMD_ID_ITEM_NOTIFY	=			111;		//道具推送(部分)
const int CMD_ID_LIST_ITEM_EFFECT		=	112;		//道具推送(部分)
const int CMD_ID_BUY_ITEM				=	113;		//道具购买
const int CMD_ID_SEARCH_FOR_BAYITEMS	=	114;		//查询购买到的道具(花钱购买到的)

const int CMD_ID_GAME_TASK		=			115;         //对局任务,新任务推送
const int CMD_ID_FINISH_GAME_TASK =			116;		 //完成任务
const int CMD_ID_TIME_GIFT		=			117;		//在线礼包领取
const int CMD_ID_QUERY_TIME_GIFT =			118;		//在线礼包查询	
const int CMD_ID_BANKRUPTCY_PROTECT	=		119;		//破产保护		
const int CMD_ID_ACHIEVE_LIST	=			120;        //成就查询，成就列表返回，查询发的数据为空
const int CMD_ID_ACHIEVE_COMPELETE	=		121;        //完成成就推送
const int CMD_ID_ACHIEVE_SET	=			122;		//设置成就，手机端暂时不用

//牌型任务
const int CMD_ID_GET_CARDTYPE_TASK	=			123;   //获取牌型任务
const int CMD_ID_CARDTYPE_TASK_FINISH		=	124;  //完成牌型任务
const int CMD_ID_USER_COINS_UPDATE		=	126;  //玩家游戏币更新

const int CMD_ID_GET_MAIL_COUNT		=			130;	//获取邮件数量
const int CMD_ID_GET_MAILS_LIST		=			131;	//获取邮件列表内容
const int CMD_ID_DEL_MAILS 			=			132;	//删除邮件

const int CMD_ID_LIMIT_GOODS		=			140;	//查询时效性物品
const int CMD_ID_GET_LIMIT_GOODS	=			141;	//领取时效性物品

const int CMD_ID_GET_ACHIEVE_AWARD			=			145;    //领取奖品（成就乱七八糟的东西）

//新的对局任务
const int CMD_ID_GET_PUBLIC_TASK			= 146;//玩家自己的公共对局查询
const int CMD_ID_FINISH_PUBLIC_TASK			= 147;//完成公共对局的消息推送
const int CMD_ID_GET_PUBLIC_TASK_GOODS		= 148;//获取完成公共对局后的宝箱信息
const int CMD_ID_GET_PUBLIC_TASK_REWARD		= 149;//公共对局抽奖
const int CMD_ID_GET_PUBLIC_TASK_BUY		= 150;//公共对局购买剩余宝箱

const int CMD_ID_FIRST_PAY_MSG				= 151;//首冲信息
const int CMD_ID_FIRST_PAY_GIVING			= 152;//首冲奖励
const int CMD_ID_PRAY_MAMMON				= 153;//拜财神
const int CMD_ID_PUSH_BOX					= 154;//推送回流礼包
const int CMD_ID_MONEYTREE_QUERY			= 155;//摇钱树查询玩家结果数量
const int CMD_ID_MONEYTREE_GET				= 156;//玩家领取已经结好的果实
const int CMD_ID_CRAZYTREE_QUERY			= 157;//查询玩家的疯狂摇钱树
const int CMD_ID_CRAZYTREE_GET				= 158;//疯狂摇钱树进行摇一摇的操作


const int CMD_ID_EXCHANGE_TO_COIN			= 160;//钻石兑换游戏豆
const int CMD_ID_MY_GIFT_MSG				= 161;//自己的表情信息
const int CMD_ID_INTERACTIVE_EXPR			= 162;//互动表情交互
//关卡系统
/////////////////////////////////////////////////////////////////////////////
const int CMD_ID_GET_UNLOCK_LEVEL			= 170;//请求获取解锁的关卡列表
const int CMD_ID_GET_CURRENT_LEVEL			= 171;//请求获取当前关卡的详细信息
const int CMD_ID_REQ_START_LEVEL_GAME		= 172;//请求开始闯关
const int CMD_ID_REQ_RESTART_LEVEL_GAME		= 173;//请求重新开始闯关
const int CMD_ID_QRY_OPEN_LEVEL				= 174;//询问玩家是否开启关卡
const int CMD_ID_FINISH_LEVEL				= 175;//通知完成关卡任务
const int CMD_ID_NO_FINISH_LEVEL			= 176;//通知没有完成关卡任务
const int CMD_ID_NOTICE_TASK_INFO			= 177;//通知具体任务信息
const int CMD_ID_REQ_AWARD					= 178;//请求领取奖励
const int CMD_ID_QRY_STAR_LEVEL				= 179;//请求关卡星级
const int CMD_ID_OPEN_LEVEL_MODE			= 180;//通知是否开启关卡模式
const int CMD_ID_FINISH_ALL_LEVEL			= 181;//通知完成所有关卡
const int CMD_ID_ONCE_OPEN_LEVEL			= 182;//通知是否一键开启所有任务
const int CMD_ID_GET_STAGEINFO		= 183;//新版 请求还是171 响应为183
const int CMD_ID_GET_STAGEISOPEN		= 184;//登录后台主动告知前端玩家自己有没有开启过关卡，没开启，前端主动发请求，帮玩家主动开启  

const int CMD_ID_CONTINUE_WIN		= 186;//响应用户连胜信息 cmdID:186
const int CMD_ID_GET_MYCONTINUEWIN		= 187;//一局结束之后的连胜信息更新 cmdID:187

const int CMD_ID_PAYAWARD_INFO		= 190;//响应用户充值奖励信息 cmdID:190
const int CMD_ID_GET_PAYAWARD		= 191;//领奖 cmdID:191

//宠物系统
const int CMD_ID_PET_MYPETMSG       =192;//192-->响应用户宠物等级信息(登录时后台主动给)
const int CMD_ID_PET_SEARCHTHING    =193;//193-->寻宝 返回结果Ans_NormalReturn setRetCode=-109001暂无宠物  setRetCode=-109002请求的区域不存在  setRetCode=-109003玩家目前等级无法进入该区 setRetCode=-109004玩家请求的区域非当前在寻区域 setRetCode=-109005饥饿值不够 
const int CMD_ID_PET_FETCHAWARDS    =194;//194-->寻宝区域完成后的领奖 
const int CMD_ID_PET_STOPSEARCH     =195;//195-->停止寻宝  返回结果Ans_NormalReturn  0成功 小于0失败
const int CMD_ID_PET_RISELEVEL      =196;//196-->升级 返回结果Ans_NormalReturn  0成功 小于0失败
const int CMD_ID_PET_FEEDFULL       =197;//197-->喂饱 返回结果Ans_NormalReturn  0成功 小于0失败 
const int CMD_ID_PET_SEARCHCOUNTAWARDS = 198;//198-->寻宝次数奖励 返回结果Ans_NormalReturn 小于0失败
const int CMD_ID_PET_FAREEXCHANGE   =199;//199-->请求兑换
const int CMD_ID_PET_CHANGENAME     =600;//600-->修改宠物昵称
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////
const int CMD_ID_ENTER_TABLE	=			200;		 //进入桌子
const int CMD_ID_TABLE_LIST		=			201;         //桌子列表
const int CMD_ID_CHAT			=			202;		 //聊天信息

const int CMD_ID_SIT_DOWN		=			203;         //坐下
const int CMD_ID_STAND_UP		=			204;		 //站起

const int CMD_ID_LEAVE_TABLE	=			207;		 //离开
const int CMD_ID_PREPARE		=			208;        //准备

const int CMD_ID_UPDATE_PLAYER	=			210;		 //更新玩家信息通知
const int CMD_ID_PART_UPDATE_PLAYER	=		211;         //更新玩家部分信息，下行
const int CMD_ID_PLAYER_LEAVE	=			212;		 //玩家离开通知
const int CMD_ID_PLAYER_SITDOWN	=			213;		  //玩家坐下通知
const int CMD_ID_PLAYER_STANDUP =			214;		 //玩家站起通知

const int CMD_ID_SEARCH_TABLE 	=			215;		//搜索桌子
const int CMD_ID_SCENE_COUNT	=			216;		//在线人数
const int CMD_ID_TRUSTEESHIP			=	217;		//托管
const int CMD_ID_NOTIFY_TRUSTEESHIP		=	218;		//托管通知
const int CMD_ID_CHANGE_TABLE 			=	221;	//换桌

const int CMD_ID_GAME_START		=			300;		 //开始游戏
const int CMD_ID_GAME			=			302;		 //游戏部分
const int CMD_KICKED			=			303;        //被T
const int CMD_ID_END_GAME		=			305;        //游戏结束
const int CMD_ID_CAST			=			308;        //走马灯 大字报
const int CMD_ID_QUERY_KEEPLOGIN	=		312;        //获取连续登陆状态 （下行）
const int CMD_ID_KEEPLOGIN		=			313;        //领取连续登陆奖励，上下行

const int CMD_ID_GAME_CFG		=			315;		//游戏配置拉取
const int CMD_ID_GAME_CFG_UPDATE		=	316;		//游戏配置更新通知
const int CMD_ID_GAME_NEWCFG			=	317;			//新游戏配置拉取
const int CMD_ID_GAME_NEWCFG_UPDATE		=	318;		//新游戏配置更新通知
const int CMD_ID_PLAYER_READY	=			319;		//游戏中玩家准备
const int CMD_ID_GAMEPRIVATE_MSG		=		320;	//游戏内自由定义协议
const int CMD_ID_RECOMMEND_SERVER	=		321;	//登录成功之后的推荐服响应(两种情况会发：原服在玩或原服不在玩在等待比赛晋级等)
const int CMD_ID_LIMIT_ITEM	=		322;	//限时道具
const int CMD_ID_CHANGE_USERINFO	=		323;	//修改用户信息



//好友赠送，微信，QQ等好友赠送
const int CMD_ID_GAME_FRIEND_GIVING		=	605;

const int CMD_ID_SEARCHMYFARE	=			100001;        //我的话费
const int CMD_ID_APLLYFORFARE	=			100002;        //申请兑换话费
const int CMD_ID_REMAINFARE		=			100003;        //场次对应话费情况
const int CMD_ID_RANK_FARE		=			100004;        //每日之星领取

//7天礼包
const int CMD_ID_QUERY_7DAY_STATUS		=	100010;//查询7天礼包状态
const int CMD_ID_GET_7DAY_GIFT			=	100011;//获取7天礼包礼物
const int CMD_ID_QUERY_3DAY_STATUS			=	100012;//获取3天礼包礼物
//排行查询
const int CMD_ID_RANK_MYRANK			=	100020;//排行获取自己排名
const int CMD_ID_RANK_EVERYDAY_STAR		=	100021;//获取每日之星
const int CMD_ID_RANK_COIN_RANK			=	100022;//获取金币排行
const int CMD_ID_RANK_POINT_RANK		=	100023;//获取积分排行
const int CMD_ID_RANK_ACHIEVE_RANK		=	100024;//获取成就排行
const int CMD_ID_RANK_PLAYCOUNT_RANK	=	100025;//获取对局排行
const int CMD_ID_RANK_GRADEACTIVE_RANK	=	100026;//获取活跃等级排行
const int CMD_ID_RANK_PAYCOIN_RANK		=	100027;//获取充值排行
const int CMD_ID_RANK_WINCOIN_RANK		=	100028;//获取赢家排行
const int CMD_ID_RANK_MATCHPOINTS_RANK		=	100029;//获取比赛大师分排行
const int CMD_ID_RANK_WEEKMATCHPOINTS_RANK		=	100030;//获取比赛大师分周排行
const int CMD_ID_RANK_GLAMOURVAL_RANK		=	100031;//获取魅力值排行
const int CMD_ID_RANK_PAYCOIN_AWARD		=	100032;//充值奖励领奖
const int CMD_ID_RANK_PETFETCHNUM       = 100033;//100033 宠物昨日领奖次数排行榜
const int CMD_ID_GAME_FRIENDS_INFO		=	100034;//游戏好友数据，前端做排行

const int CMD_ID_REQ_VIP				=	100050; //查询Vip每日奖励 100050
const int CMD_ID_GET_VIP				=	100051; //领取Vip额外奖励 100051

const int CMD_ID_REQ_GRADE_GIVING		=	100060; //查询等级奖励 100060
const int CMD_ID_GET_GRADE_GIVING		=	100061; //领取等级奖励 100061
//const int CMD_ID_REQ_GRADE_UPGRADE		=	100062; //请求等级升级 100062
//const int CMD_ID_REQ_GRADE_TIPS			=	100063; //请求等级说明 100063


const int CMD_ID_REQ_RANK_AWARD			=	100070; //查看不同排行榜类型的奖励
const int CMD_ID_GET_RANK_AWARD			=	100071; //领取不同排行榜类型的奖励

//比赛
const int CMD_ID_MATCH_APPLY			=	200001;  //报名
const int CMD_ID_MATCH_CANCLE			=	200002;  //取消报名
const int CMD_ID_MATCH_EXIT				=	200003;	 //退赛
const int CMD_ID_MATCH_APPLY_INFO		=	200004;  //获取自己报名所有比赛
const int CMD_ID_MATCH_START			=	200005;  //赛前通知
const int CMD_ID_MATCH_USER_INFO		=	200006;  //查询自己包名的某个比赛
const int CMD_ID_MATCH_PLAYERS			=	200007;  //获取比赛玩家列表，返回顺序即为排名
const int CMD_ID_MATCH_MY_RESULT		=	200008;  //个人比赛结果，后台推送
const int CMD_ID_MATCH_RESULT			=	200009;	 //最终比赛结果，后台推送
const int CMD_ID_MATCH_INFO				=	200010;  //获取某个比赛信息
const int CMD_ID_MATCH_CFG				=	200011;  //获取比赛配置
const int CMD_ID_MATCH_CUR_INFO			=	200012;   //查询当前比赛信息
const int CMD_ID_MATCH_TURN_REMIAN		=	200013; //当轮剩余信息
const int CMD_ID_MATCH_TURN_RANK		=	200014; //一轮完以后，推送排名信息
//
const int CMD_ID_MATCH_FIXED_TO_CANCEL	=	200015;		//定时赛人数不足取消比赛通知
const int CMD_ID_MATCH_NOTIFY_BEFORE	=	200016;		// 定时赛赛前通知
const int CMD_ID_MATCH_GAME_START_TO_NOTIFY = 200017;	//每局比赛开始时的通知
const int CMD_ID_MATCH_NOTIFY_USER_TO_PAY = 200018;		// 补豆通知
const int CMD_ID_MATCH_MULT_INFO		= 200019;		// 拉取多个比赛

///////////////////错误码//////////////////////////////
const int ErrBaseCode 			= -101000 ;
const int ErrParameter 			= ErrBaseCode - 1 ;	//参数错误
const int ErrNotLogin	 		= ErrBaseCode - 2 ;	//尚未登录
const int ErrCertExpire 		= ErrBaseCode - 3 ;	//验证码过期
const int ErrCertInvalid 		= ErrBaseCode - 4 ;	//验证码无效
const int ErrGameClass			= ErrBaseCode - 5 ;	//
const int ErrInstanceGame		= ErrBaseCode - 6 ;	//
const int ErrGameCmdClass		= ErrBaseCode - 7 ;	//
const int ErrIllegalOperation 	= ErrBaseCode - 8;	//非法操作
const int ErrInvalidOperation 	= ErrBaseCode - 9;	//无效操作
const int ErrHadLogin			= ErrBaseCode - 10;	//无效操作
const int ErrLoginOtherPlase	= ErrBaseCode - 11;	//账号在其他地方登陆
const int ErrCoinNotEnough		= ErrBaseCode - 20;	//金币不足
const int ErrFareNotEnough		= ErrBaseCode - 21;	//话费不足

const int ErrRoomBaseCode		= -102000 ;
const int ErrRoomUserIsPlaying	= ErrRoomBaseCode - 1;	//正在玩
const int ErrRoomUserIsLooking	= ErrRoomBaseCode - 2;  //正在围观
const int ErrRoomNosuchRoom		= ErrRoomBaseCode - 3;  //没有该房间
const int ErrRoomNosuchTable	= ErrRoomBaseCode - 4;  //查询桌子, 没有该桌子

const int ErrTableBaseCode					= -103000 ;
const int ErrTableSeatNotEmpty				= ErrTableBaseCode - 1;//桌子不空闲
const int ErrTableEnterFiled				= ErrTableBaseCode - 2;//进入桌子失败
const int ErrTableEnterGameNotAllowed		= ErrTableBaseCode - 3;//进入桌子失败,游戏不允许进入
const int ErrTableSitDownFiled				= ErrTableBaseCode - 4;//桌子坐下失败
const int ErrTableStandUpFiled				= ErrTableBaseCode - 5;//桌子站起失败
const int ErrTableSitDownParamErr			= ErrTableBaseCode - 6;//桌子坐下失败,参数不对
const int ErrTableSitDownSiteBeSitedByOther	= ErrTableBaseCode - 7;//桌子坐下失败,位置已经被别人做了
const int ErrTableSitDownHadSitedOtherSite	= ErrTableBaseCode - 8;//桌子坐下失败,已经坐下了, 不能再坐
const int ErrTableStandUpFiledNotSited		= ErrTableBaseCode - 9;//桌子站起失败, 本来就没坐下
const int ErrTableLeaveFiled				= ErrTableBaseCode - 10;//桌子离开失败
const int ErrTableLeaveFiledNotMember		= ErrTableBaseCode - 11;//桌子离开失败,不是桌子的一员
const int ErrTableLeaveFiledEscapeTrusteeship	= ErrTableBaseCode - 12;//桌子离开失败,正离开托管
const int ErrTableStandUpFiledEscapeTrusteeship	= ErrTableBaseCode - 13;//桌子站起失败, 处于逃跑托管状态
const int ErrTableNotFoundTable				= ErrTableBaseCode - 14;//未找到桌子
const int ErrKickNotReadyPlayer				= ErrTableBaseCode - 15; //玩家未准备被T

const int ErrFuncBaseCode					= -105000;//功能
const int ErrFuncLukcyDraw 					= ErrFuncBaseCode - 1;
const int ErrTodayHasDoDailyAtt 			= ErrFuncBaseCode - 2;//今日已经签过到了, 不能重复签到

//道具
const int ErrFuncBaseCode_NoUserItem 		= ErrFuncBaseCode - 10;//没有该道具
const int ErrFuncBaseCode_NoDependUserItem 	= ErrFuncBaseCode - 11;//没有依赖道具
const int ErrFuncBaseCode_UserItemNotEnough = ErrFuncBaseCode - 12;//道具数量不足

const int ErrVasBaseCode					= -106000;//增值服务功能
const int ErrVasGetUserInfoFailed 			= ErrVasBaseCode - 1;//用户增值服务信息获取失败
const int ErrVasHadChgedFareThisMonth 		= ErrVasBaseCode - 2;//该月已经领取过
const int ErrVasFareNotEnough 				= ErrVasBaseCode - 3;//话费不够换取
const int ErrVasDailyStarNotFound 			= ErrVasBaseCode - 4;//每日之星未获取到
const int ErrVasDailyStarNotYou 			= ErrVasBaseCode - 5;//你不是每日之星
const int ErrVasDailyStarFareHadGot 		= ErrVasBaseCode - 6;//每日之星奖励已经领取

const int ErrMatchBaseCode					= -107000;//比赛相关
const int ErrMatchHasApplyed				= ErrMatchBaseCode - 1;//已经报名
const int ErrMatchHasNotApply				= ErrMatchBaseCode - 2;//没有报名
const int ErrMatchUserIsMatching			= ErrMatchBaseCode - 3;//玩家正在比赛
const int ErrMatchApplyCoinNotEnough		= ErrMatchBaseCode - 4;//报名费用不足
const int ErrMatchNotWorkingOnTheServer		= ErrMatchBaseCode - 5;//比赛未在该服务器上有承载
const int ErrMatchEnterCoinNotEnough		= ErrMatchBaseCode - 7; //进入比赛场, 游戏币不足(游戏币低于准入)
const int ErrMatchApplyTimeError			= ErrMatchBaseCode - 8; //报名时间冲突

const int ErrPetChangeNameErrow            =-109013;//昵称名不合法
////////////////////自定义变量/////////////////////////// 
const unsigned int  NORMAL_RET_SUCCESS	=		0;		//normal协议返回，正常为0

#endif