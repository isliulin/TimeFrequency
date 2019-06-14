#ifndef	__EXT_CTX__
#define	__EXT_CTX__







#include "ext_type.h"







#define	EXT_DRV_NUM		2
#define	EXT_MGR_NUM		6
#define	EXT_OUT_NUM		30
#define	EXT_GRP_NUM		3


#define	EXT_1_OUT_LOWER		23
#define	EXT_1_OUT_UPPER		32

#define	EXT_1_PWR1			35
#define	EXT_1_PWR2			36

#define	EXT_1_MGR_PRI		37
#define	EXT_1_MGR_RSV		38

#define	EXT_1_OUT_OFFSET	(EXT_1_OUT_LOWER)

#define	EXT_2_OUT_LOWER		39
#define	EXT_2_OUT_UPPER		48

#define	EXT_2_PWR1			51
#define	EXT_2_PWR2			52

#define	EXT_2_MGR_PRI		53
#define	EXT_2_MGR_RSV		54

#define	EXT_2_OUT_OFFSET	(EXT_2_OUT_LOWER - 10)

#define	EXT_3_OUT_LOWER		55
#define	EXT_3_OUT_UPPER		66//58��59��ʹ��

#define	EXT_3_PWR1			67
#define	EXT_3_PWR2			68

#define	EXT_3_MGR_PRI		69
#define	EXT_3_MGR_RSV		70

#define	EXT_3_OUT_OFFSET	(EXT_3_OUT_LOWER - 20)








#define	EXT_SAVE_PATH	"/var/p300file"
#define	EXT_SAVE_ADDR	0x1F0000








enum
{
    EXT_NONE	= 'O',
    EXT_PWR		= 'M',
    EXT_MGR		= 'f',
    EXT_OUT16	= 'J',
    EXT_OUT32	= 'a',
    EXT_DRV		= 'd',
    EXT_OUT32S	= 'h',
    EXT_OUT16S	= 'i'
};












struct extdrv
{
    /*
      1 ��DRV
      2 ��DRV
      3 ͨ�Ź���
      4 δ����
    */
    u8_t drvPR[EXT_GRP_NUM];

    /*
      DRV��MGR֮�������״̬��1���ֽ�
      1	δ����
      0	������
      0100Y3Y2Y1Y0
      Y0-Y2���ֱ��ʾDRV��MGR(1-3)֮�������״̬
    */
    u8_t drvAlm;

    /*�汾��Ϣ*/
    u8_t drvVer[23];
};







struct extmgr
{
    /*
      1	��MGR
      2	��MGR
    */
    u8_t mgrPR;

    /*
      MGR������忨֮���ͨѶ�澯��3���ֽ�
      1	�澯
      0	����
      0100Y3Y2Y1Y0 0100Y7Y6Y5Y4 0100Y11Y10Y9Y8
      Y0-Y9���ֱ��ʾMGR������忨(1-10)֮���ͨѶ�澯
      Y10	��ʾPWR1�澯
      Y11	��ʾPWR2�澯
      Y12	1��λ���̸澯
      Y13	2��λ���̸澯
      Y14	3��λ���̸澯
      Y15	4��λ���̸澯
      Y16	5��λ���̸澯
      Y17	6��λ���̸澯
      Y18	7��λ���̸澯
      Y19	8��λ���̸澯
      Y20	9��λ���̸澯
      Y21	10��λ���̸澯
      Y22	11��λ���̸澯
      Y24	12��λ���̸澯
      Y24	13��λ���̸澯
      Y25	14��λ���̸澯
    */
    u8_t mgrAlm[8];

    /*�汾��Ϣ*/
    u8_t mgrVer[23];
};







struct extout
{
    /* ʱ�ӵȼ� */
    u8_t outSsm[3];

    /*
      �ź�����
      0��2.048Mhz
      1��2.048Mbit/s
      2�������
    */
    u8_t outSignal[17];

    /*
      ��һ���ֽڱ�ʾ<mode>���ڶ����ֽڱ�ʾ<out-sta>
      <mode> ::= 0|1����ͨģʽ|����ģʽ
      <out-sta> ::= 0|1������|����
    */
    u8_t outPR[4];

    /*
      �澯��6���ֽ�
      0100Y3Y2Y1Y0 0100Y7Y6Y5Y4 0100Y11Y10Y9Y8
      0100Y15Y14Y13Y12 0100Y19Y18Y17Y16 0100Y23Y22Y21Y20
      Y0		����10M����澯
      Y1		����10M����澯
      Y2~Y17	1~16��·/�飩����澯
    */
    u8_t outAlm[7];

    /*�汾��Ϣ*/
    u8_t outVer[23];
};








struct extsave
{
    /*
      'E'	FLASH�ѱ�������
    */
    u8_t flashMark;

    /*
      1 ��DRV
      2 ��DRV
    */
    u8_t drvPR[EXT_DRV_NUM][EXT_GRP_NUM];

    /*
      1	��MGR
      2	��MGR
    */
    u8_t mgrPR[EXT_MGR_NUM];

    /* ʱ�ӵȼ� */
    u8_t outSsm[EXT_OUT_NUM][3];

    /*
      �ź�����
      0��2.048Mhz
      1��2.048Mbit/s
      2�������
    */
    u8_t outSignal[EXT_OUT_NUM][17];

    /*
      ��һ���ֽڱ�ʾ<mode>���ڶ����ֽڱ�ʾ<out-sta>
      <mode> ::= 0|1����ͨģʽ|����ģʽ
      <out-sta> ::= 0|1������|����
    */
    u8_t outPR[EXT_OUT_NUM][4];
    unsigned char onlineSta;
};








struct extctx
{
    //ext save
    struct extsave save;

    // MCP��DRV��ͨ�Ÿ澯
    // 1	�澯
    // 0	����
    u8_t extMcpDrvAlm[2];

    /* 2��DRV */
    struct extdrv drv[EXT_DRV_NUM];

    /* �忨���ͣ�O ���̣�M PWR��f MGR��J OUT16��a OUT32 */
    u8_t extBid[EXT_GRP_NUM][15];

    /* 6��MGR */
    struct extmgr mgr[EXT_MGR_NUM];

    /* 30������忨 */
    struct extout out[EXT_OUT_NUM];

    u8_t old_drv_mgr_sta[32];
    u8_t new_drv_mgr_sta[32];
};








#endif//__EXT_CTX__


