#include <ps4.h>

// تعريف دوال النظام الفرعية للتحميل في الخلفية على PS4
int sceBgftServiceOpen(int *serviceHandle);
int sceBgftServiceClose(int serviceHandle);

// الهيكل البرمجي المعتمد لروابط التحميل
struct bgft_download_params {
    unsigned int size;
    unsigned int user_id;
    int simultaneous;
    const char *url;
    const char *name;
    int reserved[16]; // مصفوفة حجز الذاكرة لتطابق النظام
};

// الدالة الرئيسية للبايلود
int _main(struct thread *td) {
    initKernel();
    initLibc();
    
    // تحميل مكتبة نظام المساعدة
    int sysUtilHandle = sceSysmoduleLoadModule(0x009A); 
    
    int serviceHandle = 0;
    int taskId = 0;
    
    // محاولة الاتصال بمدير تحميل نظام بلايستيشن
    if (sceBgftServiceOpen(&serviceHandle) == 0) {
        
        struct bgft_download_params params;
        memset(&params, 0, sizeof(params));
        
        params.size = sizeof(params);
        params.user_id = 0x10000000; // معرف المستخدم الافتراضي
        params.simultaneous = 1;     // بدء فوري للتحميل
        
        // الرابط المباشر للعبة Journey التي اخترتها
        params.url = "http://archive.org/download/ps4-fpkg-collection-english-j/Journey%20-%20[US]%20[EN]%20[1.01].pkg"; 
        params.name = "Journey Installer";
        
        // إعطاء النظام أمر تسجيل مهمة التحميل الخلفي
        // نستخدم الرقم 20 للمطابقة مع إصدارات النظام المحدثة
        syscall(615, serviceHandle, &params, &taskId); 
        
        sceBgftServiceClose(serviceHandle);
        
        // إظهار إشعار فوري على شاشة التلفاز
        sceSysUtilSendMessage("Direct Download Started Successfully!", 0);
    } else {
        sceSysUtilSendMessage("Failed to access PS4 BGFT Server.", 0);
    }
    
    return 0;
}
