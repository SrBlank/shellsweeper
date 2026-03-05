pkgname=shellsweeper
pkgver=1.0.0
pkgrel=1
pkgdesc="Terminal Minesweeper built with ncurses"
arch=('x86_64')
url="https://github.com/SrBlank/shellsweeper"
license=('MIT')
depends=('ncurses')
makedepends=('cmake')
source=("$url/archive/v$pkgver.tar.gz")
sha256sums=('SKIP')

build() {
    cd "$srcdir/$pkgname-$pkgver"
    cmake -B build
    cmake --build build
}

package() {
    cd "$srcdir/$pkgname-$pkgver/build"
    install -Dm755 shellsweeper "$pkgdir/usr/bin/shellsweeper"
}