
# 導入方法

## 事前準備

　一度だけやればいい。

### Redhat系
`  dnf install gtkmm24-devel gnutls-devel libSM-devel libtool automake git `

### Debin系
`   sudo apt-get build-dep jd`

　開発環境が入っていない場合は、

`  sudo apt-get install build-essential automake autoconf-archive git`

## インストール

```
    git clone -b test --depth 1 https://github.com/yama-natuki/JD.git jd  
    cd jd  
    autoreconf -i  
    ./configure  
    make
```

　実行するには直接 src/jd を起動するか手動で /usr/bin あたりに src/jd を cp する。


# 参考
　詳しいインストールの方法は [本家のwiki](https://ja.osdn.net/projects/jd4linux/wiki/OS%2f%E3%83%87%E3%82%A3%E3%82%B9%E3%83%88%E3%83%AA%E3%83%93%E3%83%A5%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3%E5%88%A5%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB%E6%96%B9%E6%B3%95) を参照。


