<?php

namespace App\Listeners;

use Illuminate\Auth\Events\Logout;
use Illuminate\Support\Facades\DB;

class UserLogout
{
    /**
     * Create the event listener.
     *
     * @return void
     */
    public function __construct()
    {
        //
    }

    /**
     * Handle the event.
     *
     * @param  Logout  $event
     * @return void
     */
    public function handle(Logout $event)
    {
        $username = $event->user->getAuthIdentifier();
        $accessTokens = DB::select('SELECT id FROM oauth_access_tokens WHERE user_id = ?', [$username]);
        foreach ($accessTokens as $accessToken)
        {
            DB::delete('DELETE FROM oauth_access_tokens WHERE user_id = ?', [$username]);
            DB::delete('DELETE FROM oauth_refresh_tokens WHERE access_token_id = ?', [$accessToken->id]);
        }
    }
}
