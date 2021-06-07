from flask import Flask
from flask import request
from flask import render_template
from lxml import etree
import requests


app = Flask(__name__)
url = 'http://dict.cn/'


def get_explain(word: str) -> str:
    html_str = requests.get(url + word, proxies = None)
    if html_str.status_code != 200:
        return '获取单词释义失败'
    else:
        html_content = html_str.text.encode(encoding ='utf-8')
        html_parsed = etree.HTML(html_content)
        res_str = ""
        for i in range(1, len(html_parsed.xpath('//*[@class="dict-basic-ul"]/li'))):
            data1 = html_parsed.xpath('//*[@class="dict-basic-ul"]/li[' + str(i) + ']/span')[0].text
            data2 = html_parsed.xpath('//*[@class="dict-basic-ul"]/li[' + str(i) + ']/strong')[0].text
            res_str += data1 + ' ' + data2 + ' <br />'
        return res_str


@app.route('/', methods=['POST', 'GET'])
def main():
    if request.method == 'POST':
        word = request.form['word']
        return_explain = get_explain(word)
        return render_template('index.html', explain_data = return_explain)
    return render_template('index.html')


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=2000)
