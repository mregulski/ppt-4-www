var gulp = require('gulp');
var sass = require('gulp-sass');
var concat = require('gulp-concat');
var plumber = require('gulp-plumber');
var sourcemaps = require('gulp-sourcemaps');
var uglify = require('gulp-uglify');
var rename = require('gulp-rename');

var scss = {
    src: 'styles/scss/**/*.scss'
};

var css = {
    rootDir: 'styles/',
    workDir: 'styles/css/',
    workFiles: this.workDir+'*.css',
    src: 'styles/css/*.css',
};
    
var js = {
    src: 'scripts/src/**/*.js',
    rootDir: 'scripts/'
};

gulp.task('compile-sass', function() {
    return gulp.src(scss.src)
        .pipe(plumber({
            errorHandler: errorHandler
        }))
        // .pipe(sourcemaps.init())
        .pipe(sass({
            outputStyle: 'compressed'

        }))
        // .pipe(sourcemaps.write())
        .pipe(gulp.dest(css.workDir));
});

gulp.task('minify-css', ['compile-sass'], function() {
    return gulp.src(['styles/__reset.min.css', css.workDir+'*.css'])
        .pipe(concat('styles.css'))
        .pipe(gulp.dest(css.rootDir));
})

gulp.task('uglify-js', function() {
    return gulp.src(js.src)
        .pipe(uglify())
        .pipe(rename({
            suffix: ".min"
        }))
        .pipe(gulp.dest(js.rootDir))
})

gulp.task('watch', function() {
    gulp.watch([scss.src], ['minify-css']);
    gulp.watch(js.src, ['uglify-js'])
})

function errorHandler(error) {
    console.error(error.messageFormatted);
    this.emit('end');
}
