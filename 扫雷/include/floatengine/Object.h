#pragma once
#include "FloatApi.h"
#include <string>
#include "Enum.h"
#include <array>
#include <functional>
#define FOBJECT_BODY() float x, y; float image_index; Texture* sprite_index; int depth; Size m_block; float m_angle; Vector2 m_origin;
class Object
{
	int _m_obj_pro;
	std::string _m_obj_name;
	int __object_alarm_clock_timer_;

protected:
	//计时器
	static const int ALARM_EVENT_COUNT = 11;
	void reset_alarm_clock();
	std::array<void (Object::*)(), ALARM_EVENT_COUNT> alarmEvents;

	//计时器节点
	void show_object_alarm_clock_timer(Font font,float x,float y,Color col);
	int alarm_time_node[ALARM_EVENT_COUNT];
	//物体属性
	void change_name(const char* name) {
		_m_obj_name = name;
	}
	void change_pro(int pro) {
		_m_obj_pro = pro;
	}
	void Draw_Block(Color col);
	bool Is_Meeting(float _x, float _y, const Object* other);
public:
	int _ins_id;
	FOBJECT_BODY()
	Object();
	Object(const char* name,int ins_id, int pro = OBJPRO.Normal);
	~Object();
	inline void setObjName(const std::string& name) { _m_obj_name = name; }
	inline void setObjPro(const int& pro) { _m_obj_pro = pro; }
	inline const char* getObjName() const { return _m_obj_name.c_str(); }
	inline const int& getObjPro() const { return _m_obj_pro; }
	virtual void onEvent_User(int index);
	virtual void onEnter();
	virtual void onUpdate();
	virtual void onRenderBefore();
	virtual void onRender();
	virtual void onRenderNext();
	virtual void onBeginCamera();
	virtual void onEndCamera();
	//计时器
	int getAlarmCount() const {
		return ALARM_EVENT_COUNT;
	}
	void onAlarmEvent();
	virtual void onAlarmEvent0();
	virtual void onAlarmEvent1();
	virtual void onAlarmEvent2();
	virtual void onAlarmEvent3();
	virtual void onAlarmEvent4();
	virtual void onAlarmEvent5();
	virtual void onAlarmEvent6();
	virtual void onAlarmEvent7();
	virtual void onAlarmEvent8();
	virtual void onAlarmEvent9();
	virtual void onAlarmEvent10();

	//
	virtual void onDestroy();
};


