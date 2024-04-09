#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <cstdio>

struct Widget {
	Widget() { printf("Widget()\n"); }
	~Widget() { printf("~Widget()\n"); }

	Widget(int) { printf("Widget(int)\n"); }

	Widget(const Widget&) { printf("Widget(const Widget&)\n"); }

	Widget& operator=(const Widget&)
	{
		printf("Widget& =operator(const Widget&)\n");
		return *this;
	}

	Widget(Widget&&) noexcept { printf("Widget(Widget&&)\n"); }

	Widget& operator=(Widget&&) noexcept
	{
		printf("Widget& =operator(Widget&&)\n");
		return *this;
	}
};

#endif
