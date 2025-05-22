<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;

class UserMessageController extends Controller
{
    public function pushmsg(Request $request)
    {
        $msgdata = $request->only('data')['data'];
        $uid = $request->only('user')['user'];
        $time = date('Y-m-d H:i:s');
        $res = DB::insert('INSERT INTO posts(sender_id, msg_content, send_time) VALUES (?, ?, ?)', [$uid, base64_encode($msgdata), $time]);
        return response()->json(['success' => $res]);
    }

    public function getmsg(Request $request)
    {
        $uid = Auth::user()->getAuthIdentifier();
        $msgdatas = DB::select('SELECT msg_content,send_time FROM posts WHERE sender_id = ?', [$uid]);
        foreach ($msgdatas as $msgdata)
        {
            $msgdata->msg_content = base64_decode($msgdata->msg_content);
        }
        return response()->json($msgdatas);
    }
}
