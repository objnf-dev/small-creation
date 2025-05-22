<?php

Route::middleware(['auth:api', 'auth', 'msgfilter']) -> post('/push_msg', 'UserMessageController@pushmsg');

Route::middleware(['auth:api', 'auth']) -> get('/get_msg', 'UserMessageController@getmsg');
