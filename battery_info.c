#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/power_supply.h>

static int __init battery_status_init(void)
{
	char name[] = "BAT0";
	int result = 0;
	struct power_supply *psy = power_supply_get_by_name(name);
	union power_supply_propval chargenow, chargefull;
	result = psy->get_property(psy, POWER_SUPPLY_PROP_CHARGE_NOW, &chargenow);
	if (!result) {
		printk(KERN_INFO "The charge level is %d\n", chargenow.intval);
	}
	result = psy->get_property(psy, POWER_SUPPLY_PROP_CHARGE_FULL, &chargefull);
	if (!result) {
		printk(KERN_INFO "The charge level is %d\n", chargefull.intval);
	}
	return 0;
}

static void __exit battery_status_exit(void)
{
	printk(KERN_INFO "Unload battery_status module\n");
}

module_init(battery_status_init);
module_exit(battery_status_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Miroslav Tisma <tisma.etf@gmail.com>");
MODULE_DESCRIPTION("Battery status level module.");
MODULE_VERSION("0.0.1");

