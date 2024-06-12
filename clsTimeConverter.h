#pragma once
#include <cmath>

class clsTimeConverter {

public:

	// ---Years to Months---
	static float yearsToMonths(float years) {
		return years * 12;
	}
	
	// ---Years to weeks---
	static float yearsToWeeks(float years) {
		return years * 52.143;
	}
	
	// ---Years to days---
	static float yearsToDays(float years) {
		return years * 365;
	}
	
	// ---Years to hours---
	static float yearsToHours(float years) {
		return years * 8760;
	}
	
	// ---Years to minutes---
	static float yearsToMinutes(float years) {
		return years * 525600;
	}
	
	// ---Years to seconds---
	static float yearsToSeconds(float years) {
		return years * 31536000;
	}

	// ---Months to years---
	static float monthsToYears(float months) {
		return months / 12;
	}

	// ---Months to weeks---
	static float monthsToWeeks(float months) {
		return months * 4.345;
	}

	// ---Months to days---
	static float monthsToDays(float months) {
		return months * 30.417;
	}

	// ---Months to hours---
	static float monthsToHours(float months) {
		return months * 730;
	}
	
	// ---Months to minutes---
	static float monthsToMinutes(float months) {
		return months * 43800;
	}
	
	// ---Months to seconds---
	static float monthsToSeconds(float months) {
		return months * 2629746;
	}

	// ---Weeks to years---
	static float weeksToYears(float weeks) {
		return weeks / 52.143;
	}

	// ---Weeks to months---
	static float weeksToMonths(float weeks) {
		return weeks / 4.345;
	}

	// ---Weeks to days---
	static float weeksToDays(float weeks) {
		return weeks * 7;
	}

	// ---Weeks to hours---
	static float weeksToHours(float weeks) {
		return weeks * 7 * 24;
	}

	// ---Weeks to minutes---
	static float weeksToMinutes(float weeks) {
		return weeks * 7 * 24 * 60;
	}

	// ---Weeks to seconds---
	static float weeksToSeconds(float weeks) {
		return weeks * 7 * 24 * 60 * 60;
	}

	// ---Days to years---
	static float daysToYears(float days) {
		return days / 365;
	}

	// ---Days to Months---
	static float daysToMonths(float days) {
		return days / 30.417;
	}

	// ---Days to weeks---
	static float daysToWeeks(float days) {
		return days / 7;
	}

	// ---Days to Hours---
	static float daysToHours(float days) {
		return days * 24;
	}

	// ---Days to Minutes---
	static float daysToMinutes(float days) {
		return days * 24 * 60;
	}

	// ---Days to Seconds---
	static float daysToSeconds(float days) {
		return days * 24 * 60 * 60;
	}

	// ---Hours to years---
	static float hoursToYears(float hours) {
		return hours / 8760;
	}

	// ---Hours to months---
	static float hoursToMonths(float hours) {
		return hours / 730;
	}

	// ---Hours to weeks---
	static float hoursToWeeks(float hours) {
		return hours / 24 / 7;
	}
	
	// ---Hours to days---
	static float hoursToDays(float hours) {
		return hours / 24;
	}

	// ---Hours to mintutes---
	static float hoursToMinutes(float hours) {
		return hours * 60;
	}

	// ---Hours to seconds---
	static float hoursToSeconds(float hours) {
		return hours * 60 * 60;
	}

	// ---Minutes to years---
	static float minutesToYears(float minutes) {
		return minutes / 525600;
	}

	// ---Minutes to months---
	static float minutesToMonths(float minutes) {
		return minutes / 43800;
	}

	// ---Minutes to weeks---
	static float minutesToWeeks(float minutes) {
		return minutes / 10080;
	}

	// ---Minutes to days---
	static float minutesToDays(float minutes) {
		return minutes / 1440;
	}

	// ---Minutes to hours---
	static float minutesToHours(float minutes) {
		return minutes / 60;
	}

	// ---Minutes to seconds---
	static float minutesToSeconds(float minutes) {
		return minutes * 60;
	}

	// ---seconds to years---
	static float secondsToYears(float seconds) {
		return seconds / 31536000;
	}

	// ---seconds to months---
	static float secondsToMonths(float seconds) {
		return seconds / 2629746;
	}

	// ---seconds to Weeks---
	static float secondsToWeeks(float seconds) {
		return seconds / 604800;
	}

	// ---seconds to Days---
	static float secondsToDays(float seconds) {
		return seconds / 86400;
	}

	// ---seconds to hours---
	static float secondsToHours(float seconds) {
		return seconds / 3600;
	}

	// ---seconds to minutes---
	static float secondsToMinutes(float seconds) {
		return seconds / 60;
	}

	// ---Task duration in seconds---
	static float taskDurationInSeconds(short days, short hours, short minutes, short seconds)
	{
		return (days * 24 * 60 * 60) + (hours * 60 * 60) + (minutes * 60) + seconds;
	}

	// ---Seconds to taskDuration---
	struct stTaskDuration
	{
		int days = 0, hours = 0, minutes = 0, seconds = 0;
	};
	static stTaskDuration secondsToTaskDuration(int total_seconds)
	{
		stTaskDuration task_duration;
		const int seconds_per_day = 24 * 60 * 60;
		const int seconds_per_hour = 60 * 60;
		const int seconds_per_minute = 60;

		int remainder = 0;
		task_duration.days = floor(total_seconds / seconds_per_day);
		remainder = total_seconds % seconds_per_day;

		task_duration.hours = floor(remainder / seconds_per_hour);
		remainder = remainder % seconds_per_hour;

		task_duration.minutes = floor(remainder / seconds_per_minute);
		remainder = remainder % seconds_per_minute;

		task_duration.seconds = remainder;

		return task_duration;
	}

	

};