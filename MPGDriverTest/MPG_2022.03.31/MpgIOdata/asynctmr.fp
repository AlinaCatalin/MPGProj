s��         �   	  ��      �   ����                                           Asynchronous Timers                              � ��Point      <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>AsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<p class="Body">This instrument driver provides timer callbacks that execute in their own threads. Because they execute in their own threads, the timer callbacks are called even when the main thread of your program is not processing events.</p>

<p class="Body">These timer callbacks are ideal for tasks, such as data acquisition, that must be executed at reliable intervals.</p>

</body>
</html>    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body onLoad="if (typeof(initPageNoAdjust) == 'function') {initPageNoAdjust();}">
<h1 class="function">NewAsyncTimer</h1>

<p class="syntax">int NewAsyncTimer (double interval, int count, int initialState, void *eventFunction, void *callbackData);</p>

<h2 class="purpose">Purpose</h2>

<p class="Body">Creates a new asynchronous timer and returns a timer ID you can use to identify the timer in subsequent function calls.</p>

<p class="body"><span class="Monospace">NewAsyncTimer</span> creates asynchronous timers that run in threads with priority <span class="Monospace">THREAD_PRIORITY_HIGHEST</span> (2).</p> 

<p class="body"><span class="Platform">RT</span> <span class="Monospace">NewAsyncTimer</span> creates asynchronous timers that run in threads with a priority of 2. To specify a different priority, call <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','FunctionReference/cviNewAsyncTimerWithPriority.htm')">NewAsyncTimerWithPriority</a>.</p>

<table class="Borderless">
<tr>
<td class="Icon"><img src="note.gif"></td>
<td>
<strong>Note</strong>&nbsp;&nbsp;You can use asynchronous timers on <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibAsychronous_Timers_Control.htm')">Windows, real-time (RT), and Linux operating systems</a>.</td></tr></table>

<p class="Body">Asynchronous timer tick events can accumulate when the library thread responsible for generating timer tick events is unable to call the callback function at the specified interval. For example, the library thread could fall behind if the time to complete the callback function is longer than the specified interval. When asynchronous timer tick events accumulate, the library thread dispatches the accumulated events as quickly as possible. In this case, the interval at which the library thread generates events might be shorter than the interval you specified when you created the asynchronous timer. If the cause for the accumulated events is temporary and the library thread finishes generating the accumulated events, the library thread resumes generating events at the interval you specified when you created the asynchronous timer.</p> 

<p class="Body">On Windows, all asynchronous callback functions share a common thread. As a result, the duration of any asynchronous callback function can have an impact on all other asynchronous timers, possibly causing timer tick events to accumulate.</p>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibAsynchronousTimersControl_FunctionTree.htm')">Asynchronous Timers</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">toolbox\asynctmr.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 5.0 and later</p>

<!-- ADDITIONAL INFO END -->
    <!-- EXAMPLE LIST START -->

 <div class="none">
    <h2>Example</h2>
    <p>Refer to <span class="Monospace">toolbox\asyncdem.cws</span> for an example of using the <span class="Monospace">NewAsyncTimer</span> function.</p>
    <p class="Body"><a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('toolbox\\asyncdem.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </p>
</div>
    <!-- EXAMPLE LIST END -->
</body>
</html>    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">initialState</td>
<td class="paramDataType">integer</td>

<td>Specifies whether the timer is enabled or disabled when it is created. You can specify one of the following values:<br><br>

<ul>
<li>Pass <span class="Monospace">0</span> or select <strong>Disabled</strong> in the function panel&#8212;The timer is disabled and does not generate timer events when it is created.</li>
<li>Pass a nonzero value or select <strong>Enabled</strong> in the function panel&#8212;The timer is enabled and generates timer events when it is created.</li>
</ul>

The value of this parameter determines the value of the <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ASYNC_ATTR_ENABLED.html')">ASYNC_ATTR_ENABLED</a> attribute.<br><br>

<table class="Borderless">
<tr>
<td class="Icon"><img src="note.gif" alt="Note"></td>
<td><strong>Note</strong>&nbsp;&nbsp;If you create a new timer with an <strong>initialState</strong> of 0, you cannot enable the timer by calling <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','FunctionReference/cviResumeAsyncTimerCallbacks.htm')">ResumeAsyncTimerCallbacks</a>. Instead, you must set <span class="Monospace">ASYNC_ATTR_ENABLED</span> to <span class="Monospace">1</span> to enable the timer.</td></tr></table>
</td>
</tr>
</table>

</body>
</html>        <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">interval</td>
<td class="paramDataType">double</td>

<td>Specifies the wait interval, in seconds, between timer events.<br><br> 

The minimum interval value that you can use depends on the system that is running the asynchronous timer. If the interval is smaller than the asynchronous timer resolution supported by your system, LabWindows/CVI uses an interval equal to the resolution supported by the system. Call <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','FunctionReference/cviGetAsyncTimerResolution.htm')">GetAsyncTimerResolution</a> to get the asynchronous timer resolution for your system.</td>
</tr>
</table>

</body>
</html>
    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">count</td>
<td class="paramDataType">integer</td>

<td>Specifies the number of timer events to be generated before the timer is automatically discarded.<br><br>

If you pass a negative value, the timer will generate events until it is discarded by a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviDiscardAsyncTimer.htm')">DiscardAsyncTimer</a></span> or suspended by a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviSuspendAsyncTimerCallbacks.htm')">SuspendAsyncTimerCallbacks</a></span>.<br>

<table class="Borderless-Wide">
<tr>
<td class="Icon"><img src="note.gif"></td>
<td>
<strong>Note</strong>&nbsp;&nbsp;A value of zero will return an error.</td>
</tr>
</table>

</td>
</tr>
</table>

</body>
</html>        <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">eventFunction</td>
<td class="paramDataType">void&nbsp;*</td>

<td>Specifies the name of the user function that processes the callback. This event function (type <span class="Monospace">AsyncTimerCallbackPtr</span>) takes the same form as the timer callback function:<br><br>

<span class="Monospace">int CVICALLBACK FunctionName (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);</span><br><br>

The first parameter of the event function is reserved. <strong>timerId</strong> is the timer that caused the callback.  The types of events generated are <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviEVENTTIMERTICK.htm')">EVENT_TIMER_TICK</a></span> and <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviEVENTDISCARD.htm')">EVENT_DISCARD</a></span>. <strong>eventData1</strong> is a pointer to a double that represents the current time in seconds and is relative to the start of the first timer event. <strong>eventData2</strong> is a pointer to a double that represents the time that has elapsed since the last call to the timer callback. The elapsed time is set to zero if the callback has not been called previously. The resolution of <strong>eventData1</strong> and <strong>eventData2</strong> matches the resolution of the asynchronous timer. Callback data defined by the user also is passed to the event function.</td>
</tr>
</table>

</body>
</html>    #    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">callbackData</td>
<td class="paramDataType">void&nbsp;*</td>

<td>Specifies a pointer to user-defined data passed to the event function.</td>
</tr>
</table>

</body>
</html>    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">timerID</td>
<td class="paramDataType">integer</td>

<td>Specifies the ID that is used to reference the timer in subsequent
function calls. Negative values indicate that an error occurred.<br><br>

<table>
<tr><td><strong>Error Codes:</strong></td><td></td></tr>

<tr><td><span class="nobreak">&ndash;1</span></td><td>The system failed to allocate a timer.</td></tr>
<tr><td><span class="nobreak">&ndash;2</span></td><td>No more IDs are available to assign to a new timer.</td></tr>
<tr><td><span class="nobreak">&ndash;3</span></td><td>Not enough memory left for this operation.</td></tr>
<tr><td><span class="nobreak">&ndash;4</span></td><td>The timer with the given ID was not found.</td></tr>
<tr><td><span class="nobreak">&ndash;5</span></td><td>Initialization with a call to <span class="Monospace">NewAsyncTimer</span> was not done.</td></tr>
<tr><td><span class="nobreak">&ndash;6</span></td><td>An internal error occurred.</td></tr>
<tr><td><span class="nobreak">&ndash;7</span></td><td>The value of a parameter passed to this function was invalid.</td></tr>
<tr><td><span class="nobreak">&ndash;8</span></td><td>The functionality is only available on real-time operating systems.</td></tr>
<tr><td><span class="nobreak">&ndash;9</span></td><td>You cannot set this attribute.</td></tr>
</table>

</td>
</tr>
</table>

</body>
</html>    V 9�          Initial State                     � > -     `    Interval                          � > �     `    Count                             !� � -    `    Event Function                    (� � �    `    Callback Data                     + �w��    `    Timer ID                          Enabled 1 Disabled 0    1.0    -1    0    0    	           �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimerWithPriority</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">NewAsyncTimerWithPriority</h1>

<p class="syntax">int NewAsyncTimerWithPriority (double interval, int count, int initialState, void *eventFunction, void *callbackData, int priority);</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">This function creates a new asynchronous timer with the priority you specify and returns a timer ID you can use to identify the timer in subsequent function calls.</p>

<p class="body"><span class="platform">RT</span> <span class="Monospace">NewAsyncTimerWithPriority</span> is available only on real-time operating systems.</p>

<p class="Body">Asynchronous timer tick events can accumulate when the library thread responsible for generating timer tick events is unable to call the callback function at the specified interval. For example, the library thread could fall behind if the time to complete the callback function is longer than the specified interval. When asynchronous timer tick events accumulate, the library thread dispatches the accumulated events as quickly as possible. In this case, the interval at which the library thread generates events might be shorter than the interval you specified when you created the asynchronous timer. If the cause for the accumulated events is temporary and the library thread finishes generating the accumulated events, the library thread resumes generating events at the interval you specified when you created the asynchronous timer.</p> 

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibAsynchronousTimersControl_FunctionTree.htm')">Asynchronous Timers</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">toolbox\asynctmr.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 8.5 and later</p>

<!-- ADDITIONAL INFO END -->
</body>
</html>    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">initialState</td>
<td class="paramDataType">integer</td>

<td>Specifies whether the timer is enabled or disabled when it is created. You can specify one of the following values:<br><br>

<ul>
<li>Pass <span class="Monospace">0</span> or select <strong>Disabled</strong> in the function panel&#8212;The timer is disabled and does not generate timer events when it is created.</li>
<li>Pass a nonzero value or select <strong>Enabled</strong> in the function panel&#8212;The timer is enabled and generates timer events when it is created.</li>
</ul>

The value of this parameter determines the value of the <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ASYNC_ATTR_ENABLED.html')">ASYNC_ATTR_ENABLED</a> attribute.<br><br>

<table class="Borderless">
<tr>
<td class="Icon"><img src="note.gif" alt="Note"></td>
<td><strong>Note</strong>&nbsp;&nbsp;If you create a new timer with an <strong>initialState</strong> of 0, you cannot enable the timer by calling <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','FunctionReference/cviResumeAsyncTimerCallbacks.htm')">ResumeAsyncTimerCallbacks</a>. Instead, you must set <span class="Monospace">ASYNC_ATTR_ENABLED</span> to <span class="Monospace">1</span> to enable the timer.</td></tr></table>
</td>
</tr>
</table>

</body>
</html>        <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">interval</td>
<td class="paramDataType">double</td>

<td>Specifies the wait interval, in seconds, between timer events.<br><br> 

The minimum interval value that you can use depends on the system that is running the asynchronous timer. If the interval is smaller than the asynchronous timer resolution supported by your system, LabWindows/CVI uses an interval equal to the resolution supported  by the system. Call <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','FunctionReference/cviGetAsyncTimerResolution.htm')">GetAsyncTimerResolution</a> to get the asynchronous timer resolution for your system.</td>
</tr>
</table>

</body>
</html>
    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimerWithPriority</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">count</td>
<td class="paramDataType">integer</td>

<td>Specifies the number of timer events to be generated before the timer is automatically discarded.<br><br>

If you pass a negative value, the timer will generate events until it is discarded by a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviDiscardAsyncTimer.htm')">DiscardAsyncTimer</a></span> or suspended by a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviSuspendAsyncTimerCallbacks.htm')">SuspendAsyncTimerCallbacks</a></span>.<br>

<table class="Borderless-Wide">
<tr>
<td class="Icon"><img src="note.gif"></td>
<td>
<strong>Note</strong>&nbsp;&nbsp;A value of zero will return an error.</td>
</tr>
</table>

</td>
</tr>
</table>

</body>
</html>    *    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimerWithPriority</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">eventFunction</td>
<td class="paramDataType">void&nbsp;*</td>

<td>Specifies the name of the user function that processes the callback. This event function (type <span class="Monospace">AsyncTimerCallbackPtr</span>) takes the same form as the timer callback function:<br><br>

<span class="Monospace">int CVICALLBACK FunctionName (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);</span><br><br>

The first parameter of the event function is reserved. <strong>timerId</strong> is the timer that caused the callback.  The types of events generated are <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviEVENTTIMERTICK.htm')">EVENT_TIMER_TICK</a></span> and <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviEVENTDISCARD.htm')">EVENT_DISCARD</a></span>. <strong>eventData1</strong> is a pointer to a double that represents the current time in seconds and is relative to the start of the first timer event. <strong>eventData2</strong> is a pointer to a double that represents the time that has elapsed since the last call to the timer callback. The elapsed time is set to zero if the callback has not been called previously. The resolution of <strong>eventData1</strong> and <strong>eventData2</strong> matches the resolution of the asynchronous timer. Callback data defined by the user also is passed to the event function.</td>
</tr>
</table>

</body>
</html>    /    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimerWithPriority</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">callbackData</td>
<td class="paramDataType">void&nbsp;*</td>

<td>Specifies a pointer to user-defined data passed to the event function.</td>
</tr>
</table>

</body>
</html>    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimerWithPriority</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">timerID</td>
<td class="paramDataType">integer</td>

<td>Specifies the ID that is used to reference the timer in subsequent
function calls. Negative values indicate that an error occurred.<br><br>

<table>
<tr><td><strong>Error Codes:</strong></td><td></td></tr>
<tr><td><span class="nobreak">&ndash;1</span></td><td>The system failed to allocate a timer.</td></tr>
<tr><td><span class="nobreak">&ndash;2</span></td><td>No more IDs are available to assign to a new timer.</td></tr>
<tr><td><span class="nobreak">&ndash;3</span></td><td>Not enough memory left for this operation.</td></tr>
<tr><td><span class="nobreak">&ndash;4</span></td><td>The timer with the given ID was not found.</td></tr>
<tr><td><span class="nobreak">&ndash;5</span></td><td>Initialization with a call to <span class="Monospace">NewAsyncTimer</span> was not done.</td></tr>
<tr><td><span class="nobreak">&ndash;6</span></td><td>An internal error occurred.</td></tr>
<tr><td><span class="nobreak">&ndash;7</span></td><td>The value of a parameter passed to this function was invalid.</td></tr>
<tr><td><span class="nobreak">&ndash;8</span></td><td>The functionality is only available on real-time operating systems.</td></tr>
<tr><td><span class="nobreak">&ndash;9</span></td><td>You cannot set this attribute.</td></tr>
</table>

</td>
</tr>
</table>

</body>
</html>    i    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>NewAsyncTimerWithPriority</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">priority</td>
<td class="paramDataType">integer</td>

<td>Specifies the priority of the thread that runs the asynchronous timer.<br><br>

The thread priority can be any value from -15 to 15. The default priority of a thread in the system is 0. The operating system scheduler runs at priority level 9. Any threads running at a priority level equal to or higher than 9 are not subject to timeslicing by the scheduler and will run until they yield the CPU or are preempted by a higher priority thread.

Specifying a priority of 2 is equivalent to calling <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','FunctionReference/cviNewAsyncTimer.htm')">NewAsyncTimer</a></span>.</td>
</tr>
</table>

</body>
</html>    <= 9�          Initial State                     B� > -     `    Interval                          F� > �     `    Count                             K� � -    `    Event Function                    R� � �    `    Callback Data                     U  �w��    `    Timer ID                          [� �w     `    Priority                        ���� ���                                           Enabled 1 Disabled 0    1.0    -1    0    0    	            2    6This function is supported only on Real-Time systems.   @    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>DiscardAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">DiscardAsyncTimer</h1>

<p class="syntax">int DiscardAsyncTimer (int timerID);</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">This function discards the asynchronous timer with the specified timer ID. The function removes the timer from the list of existing timers and stops the timer events from occurring. The timer, thus, ceases to exist.</p>

<p class="Body">If the ID is specified as <span class="nobreak">&ndash;1</span>, all timers are discarded.</p>

<table class="Borderless-Wide">
<tr>
<td class="Icon"><img src="note.gif"></td>
<td>
<strong>Note</strong>&nbsp;&nbsp;A call to create or discard an asynchronous timer will not complete (will block) until all outstanding asynchronous callbacks return.</td>
</tr>
</table>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibAsynchronousTimersControl_FunctionTree.htm')">Asynchronous Timers</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">toolbox\asynctmr.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 5.0 and later</p>

<!-- ADDITIONAL INFO END -->
    <!-- EXAMPLE LIST START -->

 <div class="none">
    <h2>Example</h2>
    <p>Refer to <span class="Monospace">toolbox\asyncdem.cws</span> for an example of using the <span class="Monospace">DiscardAsyncTimer</span> function.</p>
    <p class="Body"><a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('toolbox\\asyncdem.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </p>
</div>
    <!-- EXAMPLE LIST END -->
</body>
</html>
    _    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>DiscardAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">timerID</td>
<td class="paramDataType">integer</td>

<td>Specifies the timer ID of the timer to be discarded. If specified as <span class="Monospace">&ndash;1</span>, all timers are discarded.</td>
</tr>
</table>

</body>
</html>    (    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>DiscardAsyncTimer</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">status</td>
<td class="paramDataType">integer</td>

<td>Return value indicating whether the function was successful. A negative number indicates that an error occurred.<br><br>

<table>
<tr><td>Return Values:</td><td></td></tr>
<tr><td>0</td><td>Success.</td></tr>
<tr><td><span class="nobreak">&ndash;1</span></td><td>The system failed to allocate a timer.</td></tr>
<tr><td><span class="nobreak">&ndash;2</span></td><td>No more IDs are available to assign to a new timer.</td></tr>
<tr><td><span class="nobreak">&ndash;3</span></td><td>Not enough memory left for this operation.</td></tr>
<tr><td><span class="nobreak">&ndash;4</span></td><td>The timer with the given ID was not found.</td></tr>
<tr><td><span class="nobreak">&ndash;5</span></td><td>Initialization with a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviNewAsyncTimer.htm')">NewAsyncTimer</a></span> was not done.</td></tr>
<tr><td><span class="nobreak">&ndash;6</span></td><td>An internal error occurred.</td></tr>
<tr><td><span class="nobreak">&ndash;7</span></td><td>The value of a parameter passed to this function was invalid.</td></tr>
<tr><td><span class="nobreak">&ndash;8</span></td><td>The functionality is only available on real-time operating systems.</td></tr>
<tr><td><span class="nobreak">&ndash;9</span></td><td>You cannot set this attribute.</td></tr>
</table>

</td>
</tr>
</table>

</body>
</html>    j� > -      `    Timer ID                          m( �w��    `    Status                                 	           �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>SuspendAsyncTimerCallbacks</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">SuspendAsyncTimerCallbacks</h1>

<p class="syntax">int SuspendAsyncTimerCallbacks ();</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">This function stops all timer callbacks until you call <a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviResumeAsyncTimerCallbacks.htm')">ResumeAsyncTimerCallbacks</a>.</p>  

<table class="Borderless">
<tr>
<td class="Icon"><img src="note.gif" alt="Note"></td>
<td><strong>Note</strong>&nbsp;&nbsp;<span class="Monospace">SuspendAsyncTimerCallbacks</span> does not change the value of the <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ASYNC_ATTR_ENABLED.html')">ASYNC_ATTR_ENABLED</a> attribute for individual timers. If you want to disable an individual timer rather than suspend all timers, set the <span class="Monospace">ASYNC_ATTR_ENABLED</span> attribute to 0.</td></tr></table>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibAsynchronousTimersControl_FunctionTree.htm')">Asynchronous Timers</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">toolbox\asynctmr.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 5.0 and later</p>

<!-- ADDITIONAL INFO END -->
</body>
</html>
    1    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>SuspendAsyncTimerCallbacks</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">status</td>
<td class="paramDataType">integer</td>

<td>Return value indicating whether the function was successful. A negative number indicates that an error occurred.<br><br>

<table>
<tr><td>Return Values:</td><td></td></tr>
<tr><td>0</td><td>Success.</td></tr>
<tr><td><span class="nobreak">&ndash;1</span></td><td>The system failed to allocate a timer.</td></tr>
<tr><td><span class="nobreak">&ndash;2</span></td><td>No more IDs are available to assign to a new timer.</td></tr>
<tr><td><span class="nobreak">&ndash;3</span></td><td>Not enough memory left for this operation.</td></tr>
<tr><td><span class="nobreak">&ndash;4</span></td><td>The timer with the given ID was not found.</td></tr>
<tr><td><span class="nobreak">&ndash;5</span></td><td>Initialization with a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviNewAsyncTimer.htm')">NewAsyncTimer</a></span> was not done.</td></tr>
<tr><td><span class="nobreak">&ndash;6</span></td><td>An internal error occurred.</td></tr>
<tr><td><span class="nobreak">&ndash;7</span></td><td>The value of a parameter passed to this function was invalid.</td></tr>
<tr><td><span class="nobreak">&ndash;8</span></td><td>The functionality is only available on real-time operating systems.</td></tr>
<tr><td><span class="nobreak">&ndash;9</span></td><td>You cannot set this attribute.</td></tr>
</table>

</td>
</tr>
</table>

</body>
</html>    {� �w��    `    Status                             	           �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>ResumeAsyncTimerCallbacks</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">ResumeAsyncTimerCallbacks</h1>

<p class="syntax">int ResumeAsyncTimerCallbacks ();</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">This function cancels the effect of a call to <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','FunctionReference/cviSuspendAsyncTimerCallbacks.htm')">SuspendAsyncTimerCallbacks</a>.</p>

<table class="Borderless">
<tr>
<td class="Icon"><img src="note.gif" alt="Note"></td>
<td><strong>Note</strong>&nbsp;&nbsp;<span class="Monospace">ResumeAsyncTimerCallbacks</span> does not change the value of the <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ASYNC_ATTR_ENABLED.html')">ASYNC_ATTR_ENABLED</a> attribute for individual timers. If you created a timer with an <strong>initialState</strong> of 0 or set <span class="Monospace">ASYNC_ATTR_ENABLED</span> to 0 for a timer, you cannot enable that timer by calling <span class="Monospace">ResumeAsyncTimerCallbacks</span>. Instead, you must set the <span class="Monospace">ASYNC_ATTR_ENABLED</span> attribute to <span class="Monospace">1</span> to enable the timer.</td></tr></table>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibAsynchronousTimersControl_FunctionTree.htm')">Asynchronous Timers</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">toolbox\asynctmr.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 5.0 and later</p>

<!-- ADDITIONAL INFO END -->
</body>
</html>    2    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>ResumeAsyncTimerCallbacks</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">status</td>
<td class="paramDataType">integer</td>

<td>Return value indicating whether the function was successful. A negative number indicates that an error occurred.<br><br>

<table>
<tr><td>Return Values:</td><td></td></tr>
<tr><td>0</td><td>Success.</td></tr>
<tr><td><span class="nobreak">&ndash;1</span></td><td>The system failed to allocate a timer.</td></tr>
<tr><td><span class="nobreak">&ndash;2</span></td><td>No more IDs are available to assign to a new timer.</td></tr>
<tr><td><span class="nobreak">&ndash;3</span></td><td>Not enough memory left for this operation.</td></tr>
<tr><td><span class="nobreak">&ndash;4</span></td><td>The timer with the given ID was not found.</td></tr>
<tr><td><span class="nobreak">&ndash;5</span></td><td>Initialization with a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviNewAsyncTimer.htm')">NewAsyncTimer</a></span> was not done.</td></tr>
<tr><td><span class="nobreak">&ndash;6</span></td><td>An internal error occurred.</td></tr>
<tr><td><span class="nobreak">&ndash;7</span></td><td>The value of a parameter passed to this function was invalid.</td></tr>
<tr><td><span class="nobreak">&ndash;8</span></td><td>The functionality is only available on real-time operating systems.</td></tr>
<tr><td><span class="nobreak">&ndash;9</span></td><td>You cannot set this attribute.</td></tr>
</table>

</td>
</tr>
</table>

</body>
</html>

    �� �w��    `    Status                             	           �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>SetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">SetAsyncTimerAttribute</h1>

<p class="syntax">int SetAsyncTimerAttribute (int timerID, int timerAttribute, . . .);</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">This function sets an attribute for the timer with the given ID.</p>

<p class="Body">The attributes that can be set are the Interval, Count, Enabled, Callback Data, or Callback Function attributes.</p>  

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibAsynchronousTimersControl_FunctionTree.htm')">Asynchronous Timers</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">toolbox\asynctmr.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 5.0 and later</p>

<!-- ADDITIONAL INFO END -->
    <!-- EXAMPLE LIST START -->

 <div class="none">
    <h2>Example</h2>
    <p>Refer to <span class="Monospace">toolbox\asyncdem.cws</span> for an example of using the <span class="Monospace">SetAsyncTimerAttribute</span> function.</p>
    <p class="Body"><a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('toolbox\\asyncdem.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </p>
</div>
    <!-- EXAMPLE LIST END -->
</body>
</html>    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>SetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">timerID</td>
<td class="paramDataType">integer</td>

<td>Specifies the ID of the timer for which you want to set the desired attribute. This is the value returned by a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviNewAsyncTimer.htm')">NewAsyncTimer</a></span>.</td>
</tr>
</table>

</body>
</html>        <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">

<title>SetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">timerAttribute</td>
<td class="paramDataType">integer</td>

<td>The <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ListOfAsyncTimerAttrs.html')">asynchronous timer attribute</a> value to set.<br><br>

In the function panel, when you click the control or press &lt;Enter&gt;, &lt;Spacebar&gt;, or &lt;Ctrl-down arrow&gt;, a dialog box appears containing a hierarchical list of the available attributes. Attributes whose values cannot be obtained are dimmed. Help text is shown for each attribute. To select an attribute, double-click it or select it and then press &lt;Enter&gt;.<br><br>

If the attribute shown in this ring control has named constants as valid values, you can open a list of them by moving to the Attribute Value control and pressing &lt;Enter&gt;. The Attribute Values dialog box displays the values and value help for the constants.
</td>
</tr>
</table>  

</body>
</html>    x    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">

<title>SetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">attributeValue</td>
<td class="paramDataType">any&nbsp;type (passed by value)</td>

<td>The value of the specified <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ListOfAsyncTimerAttrs.html')">asynchronous timer attribute</a>.<br><br>

If the attribute shown in this control has named constants as valid values, you can open a list of them by pressing &lt;Enter&gt;. The Attribute Values dialog box displays the values and value help for the constants.</td>
</tr>
</table>

</body>
</html>    .    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>SetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">status</td>
<td class="paramDataType">integer</td>

<td>Return value indicating whether the function was successful. A negative number indicates that an error occurred.<br><br>

<table>
<tr><td>Return Values:</td><td></td></tr>
<tr><td>0</td><td>Success.</td></tr>
<tr><td><span class="nobreak">&ndash;1</span></td><td>The system failed to allocate a timer.</td></tr>
<tr><td><span class="nobreak">&ndash;2</span></td><td>No more IDs are available to assign to a new timer.</td></tr>
<tr><td><span class="nobreak">&ndash;3</span></td><td>Not enough memory left for this operation.</td></tr>
<tr><td><span class="nobreak">&ndash;4</span></td><td>The timer with the given ID was not found.</td></tr>
<tr><td><span class="nobreak">&ndash;5</span></td><td>Initialization with a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviNewAsyncTimer.htm')">NewAsyncTimer</a></span> was not done.</td></tr>
<tr><td><span class="nobreak">&ndash;6</span></td><td>An internal error occurred.</td></tr>
<tr><td><span class="nobreak">&ndash;7</span></td><td>The value of a parameter passed to this function was invalid.</td></tr>
<tr><td><span class="nobreak">&ndash;8</span></td><td>The functionality is only available on real-time operating systems.</td></tr>
<tr><td><span class="nobreak">&ndash;9</span></td><td>You cannot set this attribute.</td></tr>
</table>

</td>
</tr>
</table>

</body>
</html>
    �( > -      `    Timer ID                          �  > �    �    Timer Attribute                   �3 >�    `    Attribute Value                   �� �w��    `    Status                                             0        	               <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>GetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">GetAsyncTimerAttribute</h1>

<p class="syntax">int GetAsyncTimerAttribute (int timerID, int timerAttribute, void *attributeValue);</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">This function gets the value of the specified attribute for the timer with the given ID.</p>

<p class="Body">The attributes that can be queried are the Interval, Count, Enabled, Callback Function, Callback Data, Timer Time, or Delta Time attributes.</p>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibAsynchronousTimersControl_FunctionTree.htm')">Asynchronous Timers</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">toolbox\asynctmr.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 5.0 and later</p>

<!-- ADDITIONAL INFO END -->
    <!-- EXAMPLE LIST START -->

 <div class="none">
    <h2>Example</h2>
    <p>Refer to <span class="Monospace">toolbox\asyncdem.cws</span> for an example of using the <span class="Monospace">GetAsyncTimerAttribute</span> function.</p>
    <p class="Body"><a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('toolbox\\asyncdem.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </p>
</div>
    <!-- EXAMPLE LIST END -->
</body>
</html>    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>GetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">timerID</td>
<td class="paramDataType">integer</td>

<td>Specifies the ID of the timer for which you want to get the desired attribute. This is the value returned by a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviNewAsyncTimer.htm')">NewAsyncTimer</a></span>.</td>
</tr>
</table>

</body>
</html>    '    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">

<title>GetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">timerAttribute</td>
<td class="paramDataType">integer</td>

<td>The <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ListOfAsyncTimerAttrs.html')">asynchronous timer attribute</a> value to obtain.<br><br>

In the function panel, when you click the control or press &lt;Enter&gt;, &lt;Spacebar&gt;, or &lt;Ctrl-down arrow&gt;, a dialog box appears containing a hierarchical list of the available attributes. Attributes whose values cannot be obtained are dimmed. Help text is shown for each attribute. To select an attribute, double-click it or select it and then press &lt;Enter&gt;.<br><br>

If the attribute shown in this ring control has named constants as valid values, you can open a list of them by moving to the Attribute Value control and pressing &lt;Enter&gt;. The Attribute Values dialog box displays the values and value help for the constants.
 </td>
</tr>
</table>

</body>
</html>                        

    d    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">

<title>GetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">attributeValue</td>
<td class="paramDataType">void&nbsp;*</td>

<td>The value of the specified <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ListOfAsyncTimerAttrs.html')">asynchronous timer attribute</a>.<br><br>

If the attribute shown in this control has named constants as valid values, you can open a list of them by pressing &lt;Enter&gt;. The Attribute Values dialog box displays the values and value help for the constants.</td>
</tr>
</table>

</body>
</html>    -    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>GetAsyncTimerAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">status</td>
<td class="paramDataType">integer</td>

<td>Return value indicating whether the function was successful. A negative number indicates that an error occurred.<br><br>

<table>
<tr><td>Return Values:</td><td></td></tr>
<tr><td>0</td><td>Success.</td></tr>
<tr><td><span class="nobreak">&ndash;1</span></td><td>The system failed to allocate a timer.</td></tr>
<tr><td><span class="nobreak">&ndash;2</span></td><td>No more IDs are available to assign to a new timer.</td></tr>
<tr><td><span class="nobreak">&ndash;3</span></td><td>Not enough memory left for this operation.</td></tr>
<tr><td><span class="nobreak">&ndash;4</span></td><td>The timer with the given ID was not found.</td></tr>
<tr><td><span class="nobreak">&ndash;5</span></td><td>Initialization with a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviNewAsyncTimer.htm')">NewAsyncTimer</a></span> was not done.</td></tr>
<tr><td><span class="nobreak">&ndash;6</span></td><td>An internal error occurred.</td></tr>
<tr><td><span class="nobreak">&ndash;7</span></td><td>The value of a parameter passed to this function was invalid.</td></tr>
<tr><td><span class="nobreak">&ndash;8</span></td><td>The functionality is only available on real-time operating systems.</td></tr>
<tr><td><span class="nobreak">&ndash;9</span></td><td>You cannot set this attribute.</td></tr>
</table>

</td>
</tr>
</table>

</body>
</html>    �
 > -      `    Timer ID                          � > �    �    Timer Attribute                   �1 >�    `    Attribute Value                   �� �w��    `    Status                                             0        	           ?    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>GetAsyncTimerResolution</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">GetAsyncTimerResolution</h1>

<p class="syntax">int GetAsyncTimerResolution (double *resolution);</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">This function returns the resolution in seconds of the asynchronous timers.</p>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibAsynchronousTimersControl_FunctionTree.htm')">Asynchronous Timers</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">toolbox\asynctmr.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 8.0 and later</p>

<!-- ADDITIONAL INFO END -->
</body>
</html>
        <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>GetAsyncTimerResolution</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

<td class="paramName">resolution</td>
<td class="paramDataType">double*</td>

<td>Outputs the resolution in seconds of the asynchronous timers.</td>
</tr>
</table>

</body>
</html>    .    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>GetAsyncTimerResolution</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">status</td>
<td class="paramDataType">integer</td>

<td>Return value indicating whether the function was successful. A negative number indicates that an error occurred.<br><br>

<table>
<tr><td>Return Values:</td><td></td></tr>
<tr><td>0</td><td>Success.</td></tr>
<tr><td><span class="nobreak">&ndash;1</span></td><td>The system failed to allocate a timer.</td></tr>
<tr><td><span class="nobreak">&ndash;2</span></td><td>No more IDs are available to assign to a new timer.</td></tr>
<tr><td><span class="nobreak">&ndash;3</span></td><td>Not enough memory left for this operation.</td></tr>
<tr><td><span class="nobreak">&ndash;4</span></td><td>The timer with the given ID was not found.</td></tr>
<tr><td><span class="nobreak">&ndash;5</span></td><td>Initialization with a call to <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviNewAsyncTimer.htm')">NewAsyncTimer</a></span> was not done.</td></tr>
<tr><td><span class="nobreak">&ndash;6</span></td><td>An internal error occurred.</td></tr>
<tr><td><span class="nobreak">&ndash;7</span></td><td>The value of a parameter passed to this function was invalid.</td></tr>
<tr><td><span class="nobreak">&ndash;8</span></td><td>The functionality is only available on real-time operating systems.</td></tr>
<tr><td><span class="nobreak">&ndash;9</span></td><td>You cannot set this attribute.</td></tr>
</table>

</td>
</tr>
</table>

</body>
</html>    � > -     `    Resolution                        �4 �w��    `    Status                             	           	         ����         �  1�     K.    NewAsyncTimer                   ����         3I  `X     K.    NewAsyncTimerWithPriority       ����         by  tX     K.    DiscardAsyncTimer               ����         t�  ��     K.    SuspendAsyncTimerCallbacks      ����         �  �     K.    ResumeAsyncTimerCallbacks       ����         �B  ��     K.    SetAsyncTimerAttribute          ����         ��  ��     K.    GetAsyncTimerAttribute          ����         ��  �j     K.    GetAsyncTimerResolution                �                                     DNew Async Timer                      DNew Async Timer With Priority        DDiscard Async Timer                  DSuspend Async Timer Callbacks        DResume Async Timer Callbacks         DSet Async Timer Attribute            DGet Async Timer Attribute            DGet Async Timer Resolution      