<?php

namespace App\Http\Middleware;

use Closure;
use HTMLPurifier_Config;
use HTMLPurifier;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

class MessageFilter
{
    /**
     * Handle an incoming request.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \Closure  $next
     * @return mixed
     */
    public function handle(Request $request, Closure $next)
    {
        $data = $request->only('data')['data'];
        
        $anti_xss = HTMLPurifier_Config::createDefault();
        $anti_xss -> set('HTML.Allowed', '');
        $purifier = new HTMLPurifier($anti_xss);
        $data2 = $purifier->purify($data);

        $request->offsetSet('data', $data2);
        $user = Auth::user();
        $request->offsetSet('user', $user->getAuthIdentifier());
        return $next($request);
    }
}
