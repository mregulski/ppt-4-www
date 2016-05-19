var gulp = require('gulp');
var sass = require('gulp-sass');
var concat = require('gulp-concat');
var plumber = require('gulp-plumber');
var sourcemaps = require('gulp-sourcemaps');
var scss = 'styles/scss/**/*.scss';
var css = 'styles/css/*.css'

gulp.task('compile-sass', function() {
    console.log("compiling sass...");
    return gulp.src(scss)
        .pipe(plumber({
            errorHandler: errorHandler
        }))
        .pipe(sourcemaps.init())
        .pipe(sass({
            // outputStyle: 'compressed'

        }))
        .pipe(sourcemaps.write())
        .pipe(gulp.dest('styles/css/'));
});

gulp.task('concat-css', ['compile-sass'], function() {
    return gulp.src(['styles/__reset.css', css])
        .pipe(concat('styles.css'))
        .pipe(gulp.dest('styles'));
})

gulp.task('watch', function() {
    gulp.watch('styles/scss/**/*.scss', ['concat-css']);
})

function errorHandler(error) {
    console.error(error.messageFormatted);
    this.emit('end');
}
