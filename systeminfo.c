#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/fs.h>      // Filp
#include <asm/uaccess.h>   // Segment desc.


static int CPU_INFO(void)
{
    //fp = fopen("/proc/cpuinfo", "r");
    printk("----------CPU INFO---------- \n");
    // Create variables
    struct file *f;
    char buf[2048];
    mm_segment_t fs;
    int i;
    // Init the buffer with 0
    for(i=0;i<2048;i++)
        buf[i] = '\0';

    f = filp_open("/proc/cpuinfo", O_RDONLY, 0);
    if(f == NULL)
        printk(KERN_ALERT "filp_open error!!.\n");
    else{
      
        int lineCounter = 0; 
        char temp[256];
        int TempCounter = 0;

        fs = get_fs();
        set_fs(get_ds());
        f->f_op->read(f, buf, 2048, &f->f_pos);
        set_fs(fs);

        int j;
        for(i=0;i<256;i++)
        {
             temp[i] = '\0';
        }

        for(i=0;i<2048;i++)
        {
            if(buf[i] == '\0') break;
            if(buf[i] !='\n')
            {
                temp[TempCounter] = buf[i];
                TempCounter++;
            }
            if(buf[i] == '\n')
            {
                if(lineCounter ==0 || lineCounter == 1 || lineCounter == 4 || lineCounter == 6)
                {
                    printk(KERN_INFO "%s",temp);
                }
                for(j=0;j<256;j++)
                {
                    temp[j] = '\0';
                }
                lineCounter++;
                TempCounter = 0;
                
            }
        }

    }
    filp_close(f,NULL);
    return 0;
}


static int PROCESS_INFO(char* process_id)
{
    printk("\n----------PROCESS INFO---------- \n");  
    // Create variables
    struct file *f;
    char buf[2048];
    mm_segment_t fs;
    int i;
    // Init the buffer with 0
    for(i=0;i<2048;i++)
        buf[i] = '\0';


    char buffer[100]; //  process_id li string variable (fopen fonksiyonu için parametre...)
    snprintf(buffer,100,"/proc/%s/status",process_id);   // process_id yi iki string arasına atıp string build ederek fopen() a parametre sağlamak.
    
   
    printk("IŞLENEN COMMAND :  %s \n",buffer);

    f = filp_open(buffer, O_RDONLY, 0);    /// /proc/1/status
    if(f == NULL)
        printk(KERN_ALERT "filp_open error!!.\n");
    else{
      
        int lineCounter = 0; 
        char temp[256];
        int TempCounter = 0;

        fs = get_fs();
        set_fs(get_ds());
        f->f_op->read(f, buf, 2048, &f->f_pos);
        set_fs(fs);

        int j;
        for(i=0;i<256;i++)
        {
             temp[i] = '\0';
        }

        for(i=0;i<2048;i++)
        {
            if(buf[i] == '\0') break;
            if(buf[i] !='\n')
            {
                temp[TempCounter] = buf[i];
                TempCounter++;
            }
            if(buf[i] == '\n')
            {
                if(lineCounter ==0 || lineCounter == 2 || lineCounter == 5 || lineCounter == 6 || lineCounter == 8)
                {
                    printk(KERN_INFO "%s",temp);
                }
                for(j=0;j<256;j++)
                {
                    temp[j] = '\0';
                }
                lineCounter++;
                TempCounter = 0;
                
            }
        }

    }
    filp_close(f,NULL);
    return 0;
}


static int ALL1(void)
{   
    printk("----------# ALL #--------- \n \n");
    // Create variables
    struct file *f;
    char buf[2048];
    mm_segment_t fs;
    int i;
    // Init the buffer with 0
    for(i=0;i<2048;i++)
    {
         buf[i] = '\0';
    }  
    f = filp_open("/proc/uptime", O_RDONLY, 0);  //"/proc/uptime"
    if(f == NULL)
    {
        printk(KERN_ALERT "filp_open error!!.\n");
    }
    else{
      
        int lineCounter = 0; 
        char temp[256];
        int TempCounter = 0;

        fs = get_fs();
        set_fs(get_ds());
        f->f_op->read(f, buf, 2048, &f->f_pos);
        set_fs(fs);

        int j;
        for(i=0;i<256;i++)
        {
             temp[i] = '\0';
        }

        for(i=0;i<2048;i++)
        {
            if(buf[i] == '\0') break;
            if(buf[i] !='\n')
            {
                temp[TempCounter] = buf[i];
                TempCounter++;
            }
            if(buf[i] == '\n')
            {   
                //printk(KERN_INFO "%s",temp);    /temp => bizim split edecegimiz string satiridir
                char* const delim = " ";     

	            char* splitted[2]; 
 
  	            char *token, *cur = temp;
	            int i = 0;
 	            while (token = strsep(&cur, delim)) {
                //printk("%s\n", token);
	            //printk("SATIR : %d \n",i);
	            spli#include <linux/init.h>tted[i] = token;
	            i++;
  	            }
	            int j;
	            for(j=0;j<2;j++)
	            {
                    if(j == 0)
                    {
                        printk("Booted Since : %s \n",splitted[j]);
                        
                    }
                    else
                    {
                        printk("Idle Since : %s \n",splitted[j]);
                    }
                    
	            	//printk("%s \n",splitted[j]);
	            }

                for(j=0;j<256;j++)
                {
                    temp[j] = '\0';
                }
                lineCounter++;
                TempCounter = 0;
                
            }
        }
    }

    return 0;
}

static int ALL2(void)
{
    // Create variables
    struct file *f;
    char buf[2048];
    mm_segment_t fs;
    int i;
    // Init the buffer with 0
    for(i=0;i<2048;i++)
    {
         buf[i] = '\0';
    }  
    f = filp_open("/proc/loadavg", O_RDONLY, 0);  // "/proc/loadavg"
    if(f == NULL)
    {
        printk(KERN_ALERT "filp_open error!!.\n");
    }
    else{
      
        int lineCounter = 0; 
        char temp[256];
        int TempCounter = 0;

        fs = get_fs();
        set_fs(get_ds());
        f->f_op->read(f, buf, 2048, &f->f_pos);
        set_fs(fs);

        int j;
        for(i=0;i<256;i++)
        {
             temp[i] = '\0';
        }

        for(i=0;i<2048;i++)
        {
            if(buf[i] == '\0') break;
            if(buf[i] !='\n')
            {
                temp[TempCounter] = buf[i];
                TempCounter++;
            }
            if(buf[i] == '\n')
            {   
                //printk(KERN_INFO "%s",temp);    /temp bizim split edecegimiz string satiridir
                char* const delim = " ";     

	            char* splitted[5]; 
 
  	            char *token, *cur = temp;
	            int i = 0;
 	            while (token = strsep(&cur, delim)) {
                //printk("%s\n", token);
	            //printk("SATIR : %d \n",i);
	            splitted[i] = token;
	            i++;
  	            }
	            int j;
	            for(j=0;j<5;j++)
	            {
                    if(j == 0)
                    {
                        printk("One Min : %s \n",splitted[j]);
                        
                    }
                    if(j == 1)
                    {
                        printk("Five Min: %s \n",splitted[j]);
                    }
                    if(j == 2)
                    {
                        printk("Ten Min : %s \n",splitted[j]);
                    }
                    if(j == 3)
                    {   
                        char* const delim = "/";                    /// "/" split islemi currently ve total icin   j == 3 ise ==> 4. column icine girince split islemini baslat
  	
	                    char* splitted2[2]; 
 
  	                    char *token, *cur = splitted[j];
	                    int i = 0;
 	                    while (token = strsep(&cur, delim)) {
                        //printk("%s\n", token);
	                    //printk("%d \n",i);
	                    splitted2[i] = token;
	                    i++;
  	                    }
	                    int a;
	                    for(a=0;a<2;a++)
	                    {
                            if(a==0)
                            {
                                printk("Currently  : %s \n",splitted2[a]);
                            }
                            else
                            {
                                printk("Total : %s \n",splitted2[a]);
                            }
                            
	                    	//printk("%s \n",splitted2[j]);
	                    }
                        //printk("Currently And Total : %s \n",splitted[j]);
                    }
                    
                    
	            	//printk("%s \n",splitted[j]);
	            }

                for(j=0;j<256;j++)
                {
                    temp[j] = '\0';
                }
                lineCounter++;
                TempCounter = 0;
                
            }
        }
    }

    return 0;
}

SYSCALL_DEFINE2(systeminfo,int,select,char*,pid)
{
    
    if(select == 0)
    {
        CPU_INFO();
    }
    if(select == 1)
    {
        ALL1();
        ALL2();
    }
    if(select == 2)
    {
        PROCESS_INFO(pid);
    }
}