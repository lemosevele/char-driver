#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

static char msg[100] = {0};
static short readPos = 0;
static int times = 0;

static int e_open(struct inode *, struct file *);
static int e_close(struct inode *, struct file *);
static ssize_t e_read(struct file *, char *, size_t, loff_t *);
static ssize_t e_write(struct file *, const char *,  size_t, loff_t *);

static struct file_operations fops = {
	.open    = e_open,
	.read    = e_read,
	.write   = e_write,
	.release = e_close,
};

int init_module(void){
	int t = register_chrdev(240, "Evele Driver", &fops);
	if(t<0) 
		printk(KERN_ALERT "Registro de dispositivo falhou... \n");
		
	else 
		printk(KERN_ALERT "Dispositivo registrado... \n");
	return 0;
}

void cleanup_module(void){
	unregister_chrdev(240, "Evele Driver");
}

static int e_open(struct inode *inod, struct file *fil){
	times++;
	printk(KERN_ALERT "Dispositivo aberto %d vezes\n ", times);
	return 0;
}

static ssize_t e_read(struct file *filp, char *buff, size_t len, loff_t *off){
	short count = 0;
	while (len && (msg[readPos]!=0)){
		put_user(msg[readPos], buff++);
		count++;
		len--;
		readPos++;
	}
	return count;
}

static ssize_t e_write(struct file *filp, const char *buff, size_t len, loff_t *off){
	short ind = len-1;
	short count = 0;
	memset(msg, 0, 100);
	readPos = 0;
	while(len>0){
		msg[count++] = buff[ind--];
		len--;
	}
	return count;
}

static int e_close(struct inode *inod, struct file *fil){
	printk(KERN_ALERT "Device closed\n");
	return 0;
}

