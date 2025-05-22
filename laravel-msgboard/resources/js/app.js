require('./bootstrap');
window.Vue = require('vue/dist/vue.common.js');
import Antd from 'ant-design-vue';
import "ant-design-vue/dist/antd.css";
Vue.use(Antd);

let MsgBoard = Vue.component('msg-board-comp',{
    data(){
        return {
            MsgBoardStyle: {
                'text-align': 'center',
                'padding': '5% 25% 0 25%'
            },
            MsgSubmitButtonStyle: {
                'margin': '5%'
            },
            usrmsgdata: "",
            msgUserName: ""
        }
    },
    methods:{
        sendmsg() {
            this.$message.loading("正在发送中...", 3);
            if(this.usrmsgdata === ""){
                this.$message.error("消息不能为空", 3);
                return;
            }

            let Cookies = document.cookie.split(';');
            let AccessData;
            for(let i=0;i<Cookies.length;i++){
                let data_arr = Cookies[i].split('=');
                if(data_arr[0].search('Authorization') !== -1){
                    AccessData = data_arr[1];
                }
            }
            window.axios.defaults.headers.common['Authorization'] = 'Bearer '+ AccessData;

            window.axios.default.post(window.location.href+"/api/push_msg", {
                    "data": this.usrmsgdata
                }).then( respond => {
                    if(respond.status === 200)
                        this.$message.success("发送成功", 3);
                    else
                        this.$message.error("发送失败", 3);
                });
        }
    },
    template: '<div v-bind:style="MsgBoardStyle"> <a-textarea placeholder="写下你想说的话吧！" :rows="10" v-model="usrmsgdata" /> \
               <a-button type="primary" id="submit-button" v-bind:style="MsgSubmitButtonStyle" v-on:click="sendmsg">发送</a-button> </div>'

});

let ShowSended = Vue.component('show-sended-comp', {
    template: '<a-card title="历史留言" style="margin: 5% 25% 0 25% "> \
                    <a-list class="msg-list" itemLayout="horizontal" :dataSource="oldmsgdata" :locale="{\'emptyText\': \' 无内容 \'}"> \
                            <a-list-item slot="renderItem" slot-scope="item, index"> \
                                <a-list-item-meta> \
                                <p slot="title">发布于 {{item.send_time}}</p> \
                                <p slot="description">{{item.msg_content}}</p> \
                                </a-list-item-meta> \
                            </a-list-item> \
                    </a-list> \
               </a-card> ',
    data(){
        return {
            oldmsgdata: []
        }
    },
    mounted() {
        this.getData((data) => {
            this.oldmsgdata = data;
        });
    },
    methods: {
        getData(callback){
            let Cookies = document.cookie.split(';');
            let AccessData;
            for(let i=0;i<Cookies.length;i++){
                let data_arr = Cookies[i].split('=');
                if(data_arr[0].search('Authorization') !== -1){
                    AccessData = data_arr[1];
                }
            }
            window.axios.defaults.headers.common['Authorization'] = 'Bearer '+ AccessData;

            window.axios.default.get(window.location.href.substring(0, window.location.href.length-4)+'/api/get_msg').then(respond => {
                let data = respond.data;
                callback(data)
            })
        }
    }
});

// Vue入口点
new Vue({
    el: '#app',
    components: {
        'msg-board':MsgBoard,
        'show-sended': ShowSended
    }
});


